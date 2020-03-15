/**
 *      Copyright (c) 2020 Jia Guo <jiag@ntesec.com.cn>
 *          
 *          Shang Hai Hua Yuan Chuang Xin Co., Ltd
 *                  All Right Reserved
 * 
 *  simpleT9 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3
 *  as published by the Free Software Foundation.
 *   
 *  simpleT9 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  version 3 along with MediaTomb; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <QDebug>
#include "key.h"
#include "keyboard.h"
#include "ui.h"
#include "globals.h"

namespace hycx {
namespace libsimpleT9 {

SimpleKey::SimpleKey(QString _name, int _type, SimpleKeyboard *_keyboard) : 
    keyName(_name), keyType(_type), keyboard(_keyboard) 
{
    
}

SimpleKey::SimpleKey(QString _name, QString _value, int _type, SimpleKeyboard *_keyboard) : 
    keyName(_name), keyValue(_value), keyType(_type), keyboard(_keyboard) 
{
    
}

DigitKey::DigitKey(QString _name, QString _value, SimpleKeyboard * _keyboard) :
	SimpleKey(_name, _value, SimpleKeyboard::KT_Digit, _keyboard)
{
}

DigitKey::~DigitKey()
{
}

int DigitKey::press()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(this->keyboard);

    if (keyName == simpleT9glb::key_backspace_name) {
        if (!nsKeyboard->isDisplayBufferStackEmpty()) {
            nsKeyboard->displayBufferStackPop();
        }
    } else {
        nsKeyboard->displayBufferStackPush(this->getKeyValue());
    }

    return 0;
}

MultiPurposeKey::MultiPurposeKey(QString _name, QString _candidateKeys, SimpleKeyboard *_keyboard) : 
    SimpleKey(_name, NonStandardKeyboard::KT_MultiPurpose, _keyboard), 
    selectInProgress(false)
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_keyboard);
    lastPressedTime = QDateTime::currentDateTime();
	QHash<QString, SimpleKey *> &_keys = nsKeyboard->getKeysPerKeyRole();
  
    /* TODO: Check the parent keyboard hash map to make sure 
     * the key name has no conflicts */

    if (_keys.find(_name) != _keys.end()) {
        /* Should throw exception here! */
    }
    
    this->keyName = _name;

    for (auto iter = _candidateKeys.begin(); 
            iter != _candidateKeys.end(); iter++) {
        this->candidateKeys.append(*iter);
    }

    lastPressedStage = NonStandardKeyboard::Press_Non;
}

MultiPurposeKey::~MultiPurposeKey()
{

}

QVector<QString> MultiPurposeKey::getCandidateKeys()
{
    return this->candidateKeys;
}

int MultiPurposeKey::getCandidateKeysCount()
{
    return getCandidateKeys().size();
}

const QString MultiPurposeKey::getKeyValue()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(keyboard);

    if (lastPressedStage >= 0 && lastPressedStage < candidateKeys.length()) {
        if (nsKeyboard->capsLockPressed) {
            return getCandidateKeys().at(lastPressedStage).toUpper();
        } else {
            return getCandidateKeys().at(lastPressedStage);
        }
    } else {
		qDebug() << "Index out of range, lastPressedStage - " << lastPressedStage;
        throw QException();
    }
}

void MultiPurposeKey::reset()
{
    lastPressedStage = NonStandardKeyboard::Press_Non;
    selectInProgress = false;
}

int MultiPurposeKey::press()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(keyboard);
	QHash<QString, SimpleKey *> &_keys = nsKeyboard->getKeysPerKeyRole();
	
    if (nsKeyboard == nullptr) {
		qDebug() << "Down casting failed, invalid keyboard pointer";
        return 0;
    }

    for (auto iter = _keys.begin(); iter != _keys.end(); iter++) {
        if (*iter != this)
        (*iter)->reset();
    }

    if (!selectInProgress) {
        /* First press, mark the timestamp */
        lastPressedStage = NonStandardKeyboard::First_Press;
        selectInProgress = true;
        nsKeyboard->displayBufferStackPush(this->getKeyValue());
        lastPressedTime = QDateTime::currentDateTime();
    } else {
        /* Continuous press, change stage (key value) */
		qDebug() << "Continuous press";
        QDateTime now = QDateTime::currentDateTime();
        int elapsedTime = lastPressedTime.msecsTo(now);

        if (elapsedTime < simpleT9glb::continuous_key_press_timeout) {
            /* Continuous press within 2 seconds */
			qDebug() << "Continuous press within 2 seconds";
            int count = this->getCandidateKeysCount();
            /* stage calculated from '0', so it should be 'count - 1' here */
            int lastStage = std::min(static_cast<int>(count-1), static_cast<int>(NonStandardKeyboard::Fifth_Press));
            if(lastPressedStage < lastStage) {
                lastPressedStage++;
            } else {
                lastPressedStage = NonStandardKeyboard::First_Press;   /* rollback */
				qDebug() << "rollback";
            }

            if (!nsKeyboard->isDisplayBufferStackEmpty()) {
                nsKeyboard->displayBufferStackPop();
            }
            
            nsKeyboard->displayBufferStackPush(this->getKeyValue());
            lastPressedTime = now;
        } else {
            /* Timeout */
			qDebug() << "Timeout";
            selectInProgress = false;
            this->press();
        }
    }

    return lastPressedStage;
}

FunctionKey::FunctionKey(QString _name, SimpleKeyboard *_keyboard) :
    SimpleKey(_name, NonStandardKeyboard::KT_Function, _keyboard)
{

}

FunctionKey::FunctionKey(QString _name, QString _value, SimpleKeyboard *_keyboard) :
    SimpleKey(_name, _value, NonStandardKeyboard::KT_Function, _keyboard)
{

}

FunctionKey::~FunctionKey()
{

}

void FunctionKey::reset()
{

}

int FunctionKey::press()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(keyboard);
    ImeWindow *imeWindow = nsKeyboard->getParentWindow();
    
    if (keyName == simpleT9glb::key_backspace_name) {
        /* Pinyin or Letter backspace */           
        if (!nsKeyboard->isDisplayBufferStackEmpty()) {
            nsKeyboard->displayBufferStackPop();
        }
    } else if (keyName == simpleT9glb::key_left_name) {
        /* Candidate Backward */        
        imeWindow->handleCandidateSelBackward(); 
    } else if (keyName == simpleT9glb::key_right_name) {
        /* Candidate Forward */
        imeWindow->handleCandidateSelForward();
    } else if (keyName == simpleT9glb::key_up_name) {
        /* Candidate Page Up */
        imeWindow->handleCandidateSelPageUp();
    } else if (keyName == simpleT9glb::key_down_name) {
        /* Candidate Page Down */
        imeWindow->handleCandidateSelPageDown();
    } else if (keyName == simpleT9glb::key_f10_name) {
        /* IME input mode switch */
        int keyRoles[] = { 
						NonStandardKeyboard::KR_Chinese, 
                     	NonStandardKeyboard::KR_English, 
                     	NonStandardKeyboard::KR_English_Capital,
                     	NonStandardKeyboard::KR_Digit,
                     	NonStandardKeyboard::KR_Punctuation
                     };
        int keyRolesLength = sizeof(keyRoles)/sizeof(keyRoles[0]);

        for (int i = 0; i < keyRolesLength; i++) {
            if (nsKeyboard->keyRole == keyRoles[i]) {
                i++;
                nsKeyboard->keyRole = keyRoles[i%keyRolesLength];
            }
        }

    	if (nsKeyboard->keyRole == NonStandardKeyboard::KR_English_Capital) {
    		nsKeyboard->capsLockPressed = true;
    	} else {
    		nsKeyboard->capsLockPressed = false;
    	}

        imeWindow->handleKeyRoleSwith();
    } else if (keyName == simpleT9glb::key_1_name) {
        /* Pinyin segmentation */ 
        nsKeyboard->displayBufferStackPush(getKeyValue());
    } else if (keyName == simpleT9glb::key_space_name) {
        /* Confirm the selection, currently we have nothing to do here */
    }

    return 0;
}

}} /* namespace */
