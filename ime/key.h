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
    static void press_Key_Backspace(FunctionKey *_this);
    static void press_Key_Left(FunctionKey *_this);
    static void press_Key_Right(FunctionKey *_this);
    static void press_Key_Up(FunctionKey *_this);
    static void press_Key_Down(FunctionKey *_this);
    static void press_Key_F10(FunctionKey *_this);
    static void press_Key_9(FunctionKey *_this);

    FunctionKey(QString _name, SimpleKeyboard *_keyboard);
    FunctionKey(QString _name, QString _value, SimpleKeyboard *_keyboard);

    virtual ~FunctionKey();

    virtual void reset();
    virtual int press();

private:
    int keyCode;    /* Standard Key Code */
};

#endif /* _KEY_H */
