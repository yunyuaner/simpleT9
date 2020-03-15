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
 *  version 3 along with simpleT9; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

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
#include "ui.h"

namespace hycx {
namespace libsimpleT9 {

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
		
    SimpleKeyboard();
    virtual ~SimpleKeyboard();
    
    virtual QString handleKeyPress(int keyCode);
    virtual void initializeKeys();
    virtual void setParentWindow(QDialog *parent);
    QDialog *getParentWindow();
    virtual QString getDisplayBuffer();
    SimpleKeyFactory &getKeyFactory();

protected:
    QString displayBuffer;
    QDialog *parentWindow;
    SimpleKeyFactory keyFactory;
};

class ImeWindow;

class NonStandardKeyboard : public SimpleKeyboard
{
friend class SimpleKey;
friend class MultiPurposeKey;
friend class FunctionKey;

public:
   	enum KeyPress_en {
        First_Press = 0, 
        Second_Press = 1, 
        Third_Press = 2, 
        Forth_Press = 3,
        Fifth_Press = 4,
        Press_Non = 0xff
   	};

    NonStandardKeyboard();
    virtual ~NonStandardKeyboard();

    virtual void initializeKeys();    
    
    virtual QString handleKeyPress(int keyCode);

    int getKeyRole() const;
    int setKeyRole(int _kr);
    
    /* Do not manipulate @displayBufferStack directly, 
     * use the following auxillary helper functions instead */
    void displayBufferStackPush(QString ch);
    QString displayBufferStackPop();
    void displayBufferStackClear();
    bool isDisplayBufferStackEmpty();
    QStack<QString> &getDisplayBufferStack();

    virtual QString getDisplayBuffer();

	QHash<QString, SimpleKey *> &getKeysPerKeyRole();
    ImeWindow *getParentWindow();

private:
    QString makePinyinDisplayContent();
    
	void initializeF1ToF10Keys(int _keyRole);
	virtual void initializeChineseKeys();
	void initializeEnglishKey_(int a_key_role);
	virtual void initializeEnglishKeys();
	virtual void initializeEnglishCapitalKeys();
	virtual void initializeDigitKeys();
    virtual void initializePunctuationKeys();

    void insertKey(int _keyRole, int _keyType, QString _key, QString _val);
    void insertMultiPurposeKey(int _keyRole, QString _key, QString _val);
    void insertFunctionKey(int _keyRole, QString _key, QString _val);
    void insertDigitKey(int _keyRole, QString _key, QString _val);

private:
    QHash<QString, SimpleKey *> *keys;	/* Different input mode mode has it's own keys */
    bool capsLockPressed;
    QStack<QString> displayBufferStack;
    int keyRole;
};

}} /* namespace */

#endif /* _KEYBOARD_H */
