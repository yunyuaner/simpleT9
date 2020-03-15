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

#ifndef _KEY_H
#define _KEY_H

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

namespace hycx {
namespace libsimpleT9 {

class SimpleKeyboard;

class SimpleKey
{
public:
    SimpleKey(QString _name, int _type, SimpleKeyboard *_keyboard);
    SimpleKey(QString _name, QString _value, int _type, SimpleKeyboard *_keyboard);
    
    virtual ~SimpleKey() {};

    virtual void reset() {};
    virtual int press() { return 0; }; 
    
    virtual const QString &getKeyName() const { return keyName; };
    virtual const QString getKeyValue() const { return keyValue; };

protected:
    QString keyName;
    QString keyValue;
    int keyType;

    SimpleKeyboard *keyboard;
};

class DigitKey : public SimpleKey
{
	public:
		DigitKey(QString _name, QString _value, SimpleKeyboard *_keyboard);
		virtual ~DigitKey();
		virtual int press();
};

class MultiPurposeKey : public SimpleKey
{
public:
    MultiPurposeKey(QString _name, QString _candidateKeys, SimpleKeyboard *_keyboard);
    virtual ~MultiPurposeKey();
    
    virtual void reset();
    virtual int press(); 
    
    virtual const QString getKeyValue();

    int getCandidateKeysCount();
    QVector<QString> getCandidateKeys();

private:
    QVector<QString> candidateKeys;
    int lastPressedStage;  /* how many continuous key pressed */
    QDateTime lastPressedTime;
    bool selectInProgress;
};

class FunctionKey: public SimpleKey
{
public:    
    FunctionKey(QString _name, SimpleKeyboard *_keyboard);
    FunctionKey(QString _name, QString _value, SimpleKeyboard *_keyboard);

    virtual ~FunctionKey();

    virtual void reset();
    virtual int press();

private:
    int keyCode;    /* Standard Key Code */
};

class SimpleKeyFactory
{
public:
    SimpleKeyFactory() {};
    virtual ~SimpleKeyFactory() {};
    SimpleKey *getKey(int keyType, QString _name, QString _value, SimpleKeyboard *_keyboard);
};

}} /* namespace */

#endif /* _KEY_H */
