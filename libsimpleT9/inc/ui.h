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
#include "vocabulary.h"
#include "keyboard.h"

namespace hycx {
namespace libsimpleT9 {

class SimpleWidget;

class ImeWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ImeWindow(QWidget *parent = nullptr);
    virtual ~ImeWindow();
    int refreshCandidate();
    const SimpleKeyboard *getKeyboard();
    QString getPinyinContent() const;

    void setParentWidget(SimpleWidget *_parentWidget);
    SimpleWidget * getParentWidget();

    void handleCandidateSelForward();
    void handleCandidateSelBackward();
    void handleCandidateSelPageUp();
    void handleCandidateSelPageDown();

    void handleKeyRoleSwith();    /* input method mode switch */

    void handleMultiPurposeKey(int key);
    void handleFunctionKey(int key);
    void handleDigitKey(int key);
    
    void handleKeyPressEvent(int key);

    bool eventFilter(QObject *obj, QEvent *event);

public:
    static int candidateCountPerPage;
    static const char *imeTitleStr;

private slots:

private:
    void showCandidateOnBoard(QString &inputText);

private:
    QVector<QLabel *> candidateLabels;
    QLabel *imeTitle;
    QLabel *imeModeSwitch;

	/* This variable is named 'imePinyin' for 
	 * historical reason, however, it will also 
	 * used to show Letters and Digits in case 
	 * of English/English Capital/Digit input mode */
	QLabel *imePinyin;	

	/* I'm planning to use this label as a blinking 
	 * letter of the current selected Pinyin, but 
	 * unfortunately, it hasn't been done yet :-( */
    QLabel *imePagerHint;

	SimplePager *pager;
    
    SimpleVocabulary *pinyinVocabulary_db;
    SimpleKeyboard *keyboard;

    SimpleWidget *parentWidget;
};

}}  /* namespace */

#endif /* _SIMPLE_H */
