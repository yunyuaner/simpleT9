#include "key.h"
#include "keyboard.h"
#include "ui.h"
#include "globals.h"

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
        std::cout << "Index out of range, lastPressedStage - " << lastPressedStage << std::endl;
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
        std::cout << "Down casting failed, invalid keyboard pointer" << std::endl;
        return 0;
    }

    for (auto iter = _keys.begin(); iter != _keys.end(); iter++) {
        if (*iter != this)
        (*iter)->reset();
    }

    if (!selectInProgress) {
        /* First press, mark the timestamp */
        lastPressedStage = NonStandardKeyboard::Press_0;
        selectInProgress = true;
        //nsKeyboard->pinyinDisplay.push(this->getKeyValue());
        nsKeyboard->displayBufferStackPush(this->getKeyValue());
        lastPressedTime = QDateTime::currentDateTime();
    } else {
        /* Continuous press, change stage (key value) */
        std::cout << "Continuous press" << std::endl;
        QDateTime now = QDateTime::currentDateTime();
        int elapsedTime = lastPressedTime.msecsTo(now);

        if (elapsedTime < simpleT9glb::continuous_key_press_timeout) {
            /* Continuous press within 2 seconds */
            std::cout << "Continuous press within 2 seconds" << std::endl;
            int count = this->getCandidateKeysCount();
            /* stage calculated from '0', so it should be 'count - 1' here */
            int lastStage = std::min(static_cast<int>(count-1), static_cast<int>(NonStandardKeyboard::Press_4));
            if(lastPressedStage < lastStage) {
                lastPressedStage++;
            } else {
                lastPressedStage = NonStandardKeyboard::Press_0;   /* rollback */
                std::cout << "rollback" << std::endl;
            }

            //if (!nsKeyboard->pinyinDisplay.isEmpty()) {
            //    nsKeyboard->pinyinDisplay.pop();
            //}

            if (!nsKeyboard->isDisplayBufferStackEmpty()) {
                nsKeyboard->displayBufferStackPop();
            }
            
            //nsKeyboard->pinyinDisplay.push(this->getKeyValue());
            nsKeyboard->displayBufferStackPush(this->getKeyValue());
            lastPressedTime = now;
        } else {
            /* Timeout */
            std::cout << "Timeout" << std::endl;
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

void FunctionKey::pressKeyBackspace(FunctionKey *_this)
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_this->keyboard);
    
    //if (!nsKeyboard->pinyinDisplay.isEmpty()) {
    //    nsKeyboard->pinyinDisplay.pop();
    //}

    if (!nsKeyboard->isDisplayBufferStackEmpty()) {
        nsKeyboard->displayBufferStackPop();
    }
}

void FunctionKey::pressKeyLeft(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handleCandidateSelBackward(); 
}

void FunctionKey::pressKeyRight(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handleCandidateSelForward(); 
}

void FunctionKey::pressKeyUp(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handleCandidateSelPageUp(); 
}

void FunctionKey::pressKeyDown(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handleCandidateSelPageDown(); 
}

void FunctionKey::pressKeyIMEInputModeSwitch(FunctionKey *_this)
{
    std::cout << "press_Key_IME_Input_Mode_Switch" << std::endl;
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_this->keyboard);
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

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handleKeyRoleSwith();
}

void FunctionKey::pressKeyPinyinSegmentation(FunctionKey *_this)
{
    std::cout << "press_Key_Pinyin_Segmentation" << std::endl;
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_this->keyboard);
    nsKeyboard->displayBufferStackPush(_this->getKeyValue());
}

int FunctionKey::press()
{
    if (keyName == simpleT9glb::key_backspace_name) {
        FunctionKey::pressKeyBackspace(this);	/* Pinyin or Letter backspace */
    } else if (keyName == simpleT9glb::key_left_name) {
        FunctionKey::pressKeyLeft(this);	/* Candidate Backward */
    } else if (keyName == simpleT9glb::key_right_name) {
        FunctionKey::pressKeyRight(this);	/* Candidate Forward */
    } else if (keyName == simpleT9glb::key_up_name) {
        FunctionKey::pressKeyUp(this);	/* Candidate Page Up */
    } else if (keyName == simpleT9glb::key_down_name) {
        FunctionKey::pressKeyDown(this);	/* Candidate Page Down */
    } else if (keyName == simpleT9glb::key_f10_name) {
        FunctionKey::pressKeyIMEInputModeSwitch(this); /* IME input mode switch */
    } else if (keyName == simpleT9glb::key_1_name) {
        FunctionKey::pressKeyPinyinSegmentation(this); /* Pinyin segmentation */ 
    } else if (keyName == simpleT9glb::key_space_name) {
        /* Confirm the selection, currently we have nothing to do here */
    }

    return 0;
}
