#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QDialog>
#include <QDateTime>
#include <QStack>
#include <QHash>
#include <QException>
#include <iostream>
#include "key.h"

class SimpleKeyboard
{
public:
    SimpleKeyboard() {};
    virtual ~SimpleKeyboard() {};
    
    virtual QString &handleKeyPress(int keyCode) { (void)keyCode; return pinyinDisplayContent; };
    virtual void initializeKeys() {};

protected:
    QString pinyinDisplayContent;
};

class NonStandardKeyboard : public SimpleKeyboard
{
friend class SimpleKey;
friend class MultiPurposeKey;
friend class FunctionKey;

public:
    enum KeyPress_en {
        Press_0 = 0, 
        Press_1 = 1, 
        Press_2 = 2, 
        Press_3 = 3,
        Press_4 = 4,
        Press_Non = 0xff
    };

    enum KeyType_en {
        KT_MultiPurpose,       
        KT_Function,
        KT_Unknown
    };

    enum KeyRole_en {
        KR_English,
        KR_English_Capital,
        KR_Chinese
    };

    NonStandardKeyboard();
    virtual ~NonStandardKeyboard();

    virtual void initializeKeys();
    virtual QString &handleKeyPress(int keyCode);
    QString &makePinyinDisplayContent();

    int getKeyRole() const { return keyRole; };
    int setKeyRole(int _kr) { keyRole = _kr; return keyRole; };

    void appendChar(QString ch) { pinyinDisplay.push(ch); };
    QString dropChar() { return pinyinDisplay.pop(); };
    void clearChars() { pinyinDisplay.clear(); };

private:
    QHash<QString, SimpleKey *> keys;
    bool capsLockPressed;
    QStack<QString> pinyinDisplay;
    int keyRole;
};

#endif /* _KEYBOARD_H */
