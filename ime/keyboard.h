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
#include "globals.h"

class SimpleKeyboard
{
public:

	enum KeyRole_en {
        KR_English,
        KR_English_Capital,
        KR_Chinese,
        KR_Digit,
        KR_Punctuation,
    };
		
	enum KeyType_en {
		KT_Letter,
		KT_Digit,
		KT_Punctuation,
		KT_Function,
        KT_MultiPurpose,       
        KT_Unknown
    };
		
    SimpleKeyboard() {};
    virtual ~SimpleKeyboard() {};
    
    virtual QString handleKeyPress(int keyCode) { (void)keyCode; return displayBuffer; };
    virtual void initializeKeys() {};
    virtual QString getDisplayBuffer() { return displayBuffer; };

protected:
    //QString pinyinDisplayContent;
    QString displayBuffer;
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

    NonStandardKeyboard();
    virtual ~NonStandardKeyboard();

    virtual void initializeKeys();
    virtual QString handleKeyPress(int keyCode);

    int getKeyRole() const { return keyRole; };
    int setKeyRole(int _kr) { keyRole = _kr; return keyRole; };

    //void appendChar(QString ch) { pinyinDisplay.push(ch); };
    //QString dropChar() { return pinyinDisplay.pop(); };
    //void clearChars() { pinyinDisplay.clear(); };
    //bool isPinyinDisplayEmpty() { return pinyinDisplay.isEmpty(); };
    
    /* Do not manipulate @displayBufferStack directly, 
     * use the following auxillary helper functions instead */
    void displayBufferStackPush(QString ch) { displayBufferStack.push(ch); };
    QString displayBufferStackPop() { return displayBufferStack.pop();       };
    void displayBufferStackClear()       { return displayBufferStack.clear(); };
    bool isDisplayBufferStackEmpty() { return displayBufferStack.isEmpty();        };
    QStack<QString> &getDisplayBufferStack() { return displayBufferStack; };

    virtual QString getDisplayBuffer();

	QHash<QString, SimpleKey *> &getKeysPerKeyRole() { return keys[keyRole]; };

private:
    QString makePinyinDisplayContent();
    
	void initializeF1ToF10Keys(int _keyRole);
	virtual void initializeChineseKeys();
	void initializeEnglishKey_(int a_key_role);
	virtual void initializeEnglishKeys();
	virtual void initializeEnglishCapitalKeys();
	virtual void initializeDigitKeys();
    virtual void initializePunctuationKeys();

private:
    QHash<QString, SimpleKey *> *keys;	/* Different input mode mode has it's own keys */
    bool capsLockPressed;
    QStack<QString> displayBufferStack;
    int keyRole;
};

#endif /* _KEYBOARD_H */
