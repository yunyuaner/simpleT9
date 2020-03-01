#include "key.h"
#include "keyboard.h"
#include "ui.h"

SimpleKey::SimpleKey(QString _name, int _type, SimpleKeyboard *_keyboard) : 
    keyName(_name), keyType(_type), keyboard(_keyboard) 
{
    
}

SimpleKey::SimpleKey(QString _name, QString _value, int _type, SimpleKeyboard *_keyboard) : 
    keyName(_name), keyValue(_value), keyType(_type), keyboard(_keyboard) 
{
    
}

MultiPurposeKey::MultiPurposeKey(QString _name, QString _candidateKeys, SimpleKeyboard *_keyboard) : 
    SimpleKey(_name, NonStandardKeyboard::KT_MultiPurpose, _keyboard), 
    selectInProgress(false)
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_keyboard);
    lastPressedTime = QDateTime::currentDateTime();
  
    /* TODO: Check the parent keyboard hash map to make sure 
     * the key name has no conflicts */

    if (nsKeyboard->keys.find(_name) != nsKeyboard->keys.end()) {
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

const QString MultiPurposeKey::getKeyValue()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(keyboard);

    if (lastPressedStage >= 0 && lastPressedStage < candidateKeys.length()) {
        if (nsKeyboard->capsLockPressed) {
            return candidateKeys.at(lastPressedStage).toUpper();
        } else {
            return candidateKeys.at(lastPressedStage);
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
    if (nsKeyboard == nullptr) {
        std::cout << "Down casting failed, invalid keyboard pointer" << std::endl;
        return 0;
    }

    for (auto iter = nsKeyboard->keys.begin(); iter != nsKeyboard->keys.end(); iter++) {
        if (*iter != this)
        (*iter)->reset();
    }

    if (!selectInProgress) {
        /* First press, mark the timestamp */
        lastPressedStage = NonStandardKeyboard::Press_0;
        //std::cout << "First press" << std::endl;
        selectInProgress = true;
        //std::cout << "Push key value '" << this->value().toStdString() << "' to pinyinDisplay" << std::endl;
        nsKeyboard->pinyinDisplay.push(this->getKeyValue());
        //std::cout << "Mark the current timestamp" << std::endl;
        lastPressedTime = QDateTime::currentDateTime();
    } else {
        /* Continuous press, change stage (key value) */
        std::cout << "Continuous press" << std::endl;
        QDateTime now = QDateTime::currentDateTime();
        int elapsedTime = lastPressedTime.msecsTo(now);

        if (elapsedTime < 1000) {
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

            //std::cout << "+++" << std::endl;
            if (!nsKeyboard->pinyinDisplay.isEmpty()) {
                nsKeyboard->pinyinDisplay.pop();
            }
            //std::cout << "push '" << this->value().toStdString() << "'" <<std::endl;
            nsKeyboard->pinyinDisplay.push(this->getKeyValue());
            lastPressedTime = now;
            //std::cout << "---" << std::endl;
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

void FunctionKey::press_Key_Backspace(FunctionKey *_this)
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_this->keyboard);
    
    if (!nsKeyboard->pinyinDisplay.isEmpty()) {
        nsKeyboard->pinyinDisplay.pop();
    }
}

void FunctionKey::press_Key_Left(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handle__Key_Left(); 
}

void FunctionKey::press_Key_Right(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handle__Key_Right(); 
}

void FunctionKey::press_Key_Up(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handle__Key_Up(); 
}

void FunctionKey::press_Key_Down(FunctionKey *_this)
{
    (void)_this;

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handle__Key_Down(); 
}

void FunctionKey::press_Key_F10(FunctionKey *_this)
{
    std::cout << "press_Key_F10" << std::endl;
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_this->keyboard);
    int keyRoles[] = { NonStandardKeyboard::KR_Chinese, 
                     NonStandardKeyboard::KR_English, 
                     NonStandardKeyboard::KR_English_Capital };
    int keyRolesLength = sizeof(keyRoles)/sizeof(keyRoles[0]);

    for (int i = 0; i < keyRolesLength; i++) {
        if (nsKeyboard->keyRole == keyRoles[i]) {
            i++;
            nsKeyboard->keyRole = keyRoles[i%keyRolesLength];
        }
    }

    if (nsKeyboard->keyRole == NonStandardKeyboard::KR_English || 
            nsKeyboard->keyRole == NonStandardKeyboard::KR_Chinese) {
        nsKeyboard->capsLockPressed = false;
    } else {
        nsKeyboard->capsLockPressed = true;
    }

    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->handle__Key_Role();
}

void FunctionKey::press_Key_9(FunctionKey *_this)
{
    std::cout << "press_Key_9" << std::endl;
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(_this->keyboard);
    nsKeyboard->appendChar(_this->getKeyValue());
}

int FunctionKey::press()
{
    if (keyName == "Backspace") {
        FunctionKey::press_Key_Backspace(this);
    } else if (keyName == "Left") {
        FunctionKey::press_Key_Left(this);
    } else if (keyName == "Right") {
        FunctionKey::press_Key_Right(this);
    } else if (keyName == "Up") {
        FunctionKey::press_Key_Up(this);
    } else if (keyName == "Down") {
        FunctionKey::press_Key_Down(this);
    } else if (keyName == "F10") {
        FunctionKey::press_Key_F10(this);
    } else if (keyName == "9") {
        FunctionKey::press_Key_9(this); 
    }

    return 0;
}
