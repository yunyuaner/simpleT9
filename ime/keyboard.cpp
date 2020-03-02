#include "keyboard.h"
#include "globals.h"

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
    bool keyCodeNotSupported = false;

    switch (keyCode) {
    case Qt::Key_0:
        _k = keys[simpleT9glb::key_0_name]; break;
    
    case Qt::Key_1:
        _k = keys[simpleT9glb::key_1_name]; break;
    
    case Qt::Key_2:
        _k = keys[simpleT9glb::key_2_name]; break;
    
    case Qt::Key_3:
        _k = keys[simpleT9glb::key_3_name]; break;
    
    case Qt::Key_4:
        _k = keys[simpleT9glb::key_4_name]; break;
    
    case Qt::Key_5:
        _k = keys[simpleT9glb::key_5_name]; break;
    
    case Qt::Key_6:
        _k = keys[simpleT9glb::key_6_name]; break;
    
    case Qt::Key_7:
        _k = keys[simpleT9glb::key_7_name]; break;
    
    case Qt::Key_8:
        _k = keys[simpleT9glb::key_8_name]; break;
    
    case Qt::Key_9:
        _k = keys[simpleT9glb::key_9_name]; break;
    
    case Qt::Key_Backspace:
        _k = keys[simpleT9glb::key_backspace_name]; break;
    
    case Qt::Key_Right:
        _k = keys[simpleT9glb::key_right_name]; break;
    
    case Qt::Key_Left:
        _k = keys[simpleT9glb::key_left_name]; break;
    
    case Qt::Key_Up:
        _k = keys[simpleT9glb::key_up_name]; break;
    
    case Qt::Key_Down:
        _k = keys[simpleT9glb::key_down_name]; break;
    
    case Qt::Key_F10:
        _k = keys[simpleT9glb::key_f10_name]; 
        pinyinDisplay.clear();
        break;
    
    default:
        //throw QException();
        std::cout << "key - " << QString::number(keyCode, 16).toStdString() << " not supported" << std::endl;
        keyCodeNotSupported = true;

    }

    if (!keyCodeNotSupported) {
        _k->press();
    }
    
    return makePinyinDisplayContent();
}

void NonStandardKeyboard::initializeKeys()
{
    SimpleKey *a_key;
   
    /* Multi-Purpose Keys, for T9 input method, they're '1' ~ '8' */
    a_key = new MultiPurposeKey(simpleT9glb::key_1_name, simpleT9glb::key_1_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_2_name, simpleT9glb::key_2_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_3_name, simpleT9glb::key_3_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_4_name, simpleT9glb::key_4_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_5_name, simpleT9glb::key_5_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_6_name, simpleT9glb::key_6_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_7_name, simpleT9glb::key_7_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new MultiPurposeKey(simpleT9glb::key_8_name, simpleT9glb::key_8_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    /* Functional Keys */
    a_key = new FunctionKey(simpleT9glb::key_9_name, simpleT9glb::key_9_value, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_0_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_backspace_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_right_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_left_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_up_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_down_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f10_name, this);
    keys.insert(a_key->getKeyName(), a_key);
    
    a_key = new FunctionKey(simpleT9glb::key_f9_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f8_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f7_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f6_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f5_name, this);
    keys.insert(a_key->getKeyName(), a_key);
    
    a_key = new FunctionKey(simpleT9glb::key_f4_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f3_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f2_name, this);
    keys.insert(a_key->getKeyName(), a_key);

    a_key = new FunctionKey(simpleT9glb::key_f1_name, this);
    keys.insert(a_key->getKeyName(), a_key);
}
