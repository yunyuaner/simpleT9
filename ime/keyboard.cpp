#include "keyboard.h"

NonStandardKeyboard::NonStandardKeyboard() : 
    capsLockPressed(false), keyRole(NonStandardKeyboard::KR_Chinese) 
{

}

NonStandardKeyboard::~NonStandardKeyboard()
{
    QList<QString> _k = keys.keys();

    for (auto iter = _k.begin(); iter != _k.end(); iter++) {
        SimpleKey *_v = keys[*iter];
        if (_v != nullptr) {
            delete _v;
        }
    }
}

QString &NonStandardKeyboard::makePinyinDisplayContent()
{
    QStack<QString> _p;
    /* We should pop then push to reverse the order, which keep 
     * the original data, so make a stack copy here */
    QStack<QString> _b(pinyinDisplay);  

    while (!_b.isEmpty()) {
        _p.push(_b.pop());
    }
  
    pinyinDisplayContent.clear();

    while (!_p.isEmpty()) {
        pinyinDisplayContent.append(_p.pop());
    }

    std::cout << "pinyinDisplayContent - " << pinyinDisplayContent.toStdString() << std::endl;

    return pinyinDisplayContent;
}

QString &NonStandardKeyboard::handleKeyPress(int keyCode)
{
    SimpleKey *_k;

    switch (keyCode) {
    case Qt::Key_0:
        _k = keys["0"]; break;
    
    case Qt::Key_1:
        _k = keys["1"]; break;
    
    case Qt::Key_2:
        _k = keys["2"]; break;
    
    case Qt::Key_3:
        _k = keys["3"]; break;
    
    case Qt::Key_4:
        _k = keys["4"]; break;
    
    case Qt::Key_5:
        _k = keys["5"]; break;
    
    case Qt::Key_6:
        _k = keys["6"]; break;
    
    case Qt::Key_7:
        _k = keys["7"]; break;
    
    case Qt::Key_8:
        _k = keys["8"]; break;
    
    case Qt::Key_9:
        _k = keys["9"]; break;
    
    case Qt::Key_Backspace:
        _k = keys["Backspace"]; break;
    
    case Qt::Key_Right:
        _k = keys["Right"]; break;
    
    case Qt::Key_Left:
        _k = keys["Left"]; break;
    
    case Qt::Key_Up:
        _k = keys["Up"]; break;
    
    case Qt::Key_Down:
        _k = keys["Down"]; break;
    
    case Qt::Key_F10:
        _k = keys["F10"]; 
        pinyinDisplay.clear();
        break;
    
    default:
        throw QException();
    }

    _k->press();
    
    return makePinyinDisplayContent();
}

void NonStandardKeyboard::initializeKeys()
{
    SimpleKey *a_key;
   
    /* Multi-Purpose Keys, for T9 input method, they're '1' ~ '8' */
    a_key = new MultiPurposeKey("1", QString("1abc"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("2", QString("2def"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("3", QString("3ghi"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("4", QString("4jkl"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("5", QString("5mno"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("6", QString("6pqrs"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("7", QString("7tuv"), this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey("8", QString("8wxyz"), this);
    keys.insert(a_key->getKeyName(), a_key);

    /* Functional Keys */
    a_key = new FunctionKey("9", "'", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("0", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("Backspace", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("Right", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("Left", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("Up", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("Down", this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey("F10", this);
    keys.insert(a_key->getKeyName(), a_key);
}
