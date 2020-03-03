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
    void handleCandidateSelForward();
    void handleCandidateSelBackward();
    void handleCandidateSelPageUp();
    void handleCandidateSelPageDown();
    void handleKeyRoleSwith();    /* input method mode switch */

    void handleMultiPurposeKey(int key);
    void handleFunctionKey(int key);
    void handleDigitKey(int key);
    
    void handleKeyPressEvent(int key);

private:
    static MainWindow *_instance;

protected:
    void eventFilterForIMEWindow(QObject *obj, QEvent *event);
    void eventFilterForMainWindow(QObject *obj, QEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

class ImeWindow : public QDialog
{
    Q_OBJECT

friend class MainWindow;

public:
    explicit ImeWindow(QWidget *parent = nullptr);
    virtual ~ImeWindow();
    int currSelected_inc(); 
    int currSelected_dec();
    int currSelected_set(int pos);
    int currSelected_get();
    int refreshCandidate();
    QVector<QLabel *> &getChnChars() { return chnChars; };
    const SimpleKeyboard *getKeyboard() { return keyboard; };
    QString getPinyinContent() const { return imePinyin->text(); };

public:
    static int chnCharCntPerPage;
    static const char *imeTitleStr;

private slots:

private:
    void ChnCharLabelHighlight(QLabel *label, bool highlight);
    //void showPinyinOnBoard(QString &inputText);
    void showCandidateOnBoard(QString &inputText);

private:
    int currSelected;
    int currPage;
    int pageCount;

    QVector<QLabel *> chnChars;
    QLabel *imeTitle;
    QLabel *imeModeSwitch;

	/* This variable is named 'imePinyin' for 
	 * historical reason, however, it will also 
	 * used to show Letters and Digits in case 
	 * of English/English Capital/Digit input mode */
	QLabel *imePinyin;	

	/* I'm planning to use this label show as a blinking 
	 * letter of the current selected Pinyin, but 
	 * unfortunately, it hasn't been done yet :-( */
    QLabel *imePagerHint;
	//QLabel *imePinyinVar;	

	SimplePager pager;
    
    const QHash<QString, QString> *pinyinSingleWord_db;
    Vocabulary *pinyinVocabulary_db;
    SimpleKeyboard *keyboard;
};

#endif /* _SIMPLE_H */
