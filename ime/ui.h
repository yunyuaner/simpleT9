#ifndef _SIMPLE_H
#define _SIMPLE_H

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
#include "pager.h"
#include "key.h"
#include "keyboard.h"
#include "../data/vocabulary.h"

class ImeWindow;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    virtual ~MainWindow() {};
    
    ImeWindow *getImeWindow() const { return imeWindow; };

    static MainWindow *getInstance(); 

protected:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QLineEdit *textInput;
    ImeWindow *imeWindow;
    bool imeWindowShown; 

private slots:

public:
    //void handle__Key_O();
    //void handle__Key_Return();
    void handle__Key_Right();
    void handle__Key_Left();
    void handle__Key_Up();
    void handle__Key_Down();
    void handle__Key_Role();    /* input method mode switch */

    void handleMultiPurposeKey(int key);
    void handleFunctionKey(int key);

    void handleKeyPressEvent(int key);

private:
    static MainWindow *_instance;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

class ImeWindow : public QDialog
{
    Q_OBJECT

friend class MainWindow;

public:
    explicit ImeWindow(QWidget *parent = nullptr);
    virtual ~ImeWindow() {};
    int currSelected_inc(); 
    int currSelected_dec();
    int currSelected_set(int pos);
    int currSelected_get();
    int refreshCandidate();
    QVector<QLabel *> &getChnChars() { return chnChars; };
    const SimpleKeyboard *getKeyboard() { return keyboard; };

public:
    static int chnCharCntPerPage;
    static const char *imeTitleStr;

private slots:

private:
    void ChnCharLabelHighlight(QLabel *label, bool highlight);
    void showPinyinOnBoard(QString &inputText);

private:
    int currSelected;
    int currPage;
    int pageCount;

    QVector<QLabel *> chnChars;
    QLabel *imeTitle;
    QLabel *imeModeSwitch;
    QLabel *imePinyin;
    QLabel *imePinyinVar;
    QLabel *imePagerHint;
    SimplePager pager;
    
    const QHash<QString, QString> *pinyinSingleWord_db;
    Vocabulary *pinyinVocabulary_db;
    SimpleKeyboard *keyboard;
};

#endif /* _SIMPLE_H */
