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
    static void pressKeyBackspace(FunctionKey *_this);        /* Qt::Key_Backspace */
    static void pressKeyLeft(FunctionKey *_this);      /* Qt::Key_Left */
    static void pressKeyRight(FunctionKey *_this);      /* Qt::Key_Right */
    static void pressKeyUp(FunctionKey *_this); /* Qt::Key_Up */
    static void pressKeyDown(FunctionKey *_this);      /* Qt::Key_Down */
    static void pressKeyIMEInputModeSwitch(FunctionKey *_this); /* Qt::Key_F10 */
    static void pressKeyPinyinSegmentation(FunctionKey *_this); /* Qt::Key_1 */

    FunctionKey(QString _name, SimpleKeyboard *_keyboard);
    FunctionKey(QString _name, QString _value, SimpleKeyboard *_keyboard);

    virtual ~FunctionKey();

    virtual void reset();
    virtual int press();

private:
    int keyCode;    /* Standard Key Code */
};

#endif /* _KEY_H */
