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

#include <cstddef>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QEvent>
#include <QHash>
#include <QString>
#include <QVector>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include "key.h"
#include "keyboard.h"
#include "pager.h"
#include "utf8_string.hpp"
#include "vocabulary.h"
#include "ui.h"
#include "globals.h"

int ImeWindow::candidateCountPerPage = simpleT9glb::max_chinese_char_candidate_per_page;
const char *ImeWindow::imeTitleStr = simpleT9glb::ime_title_string;

ImeWindow::ImeWindow(QWidget *parent) : 
    QDialog(parent),
    pinyinVocabulary_db(new SimpleVocabulary)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox_upper = new QHBoxLayout();
    QHBoxLayout *hbox_lower = new QHBoxLayout();
    
    imeTitle = new QLabel(QString::fromUtf8(reinterpret_cast<const char *>(ImeWindow::imeTitleStr)));
    imePinyin = new QLabel("");
    hbox_upper->addWidget(imeTitle);
    hbox_upper->addWidget(imePinyin);
  
    imeModeSwitch = new QLabel(simpleT9glb::key_role_type_chinese_text);
    imePagerHint = new QLabel("[0/0]");
    hbox_lower->addWidget(imeModeSwitch);
    hbox_lower->addWidget(imePagerHint);

    for (int i = 0; i < ImeWindow::candidateCountPerPage; i++) {
        QLabel *label = new QLabel("");
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        hbox_lower->addWidget(label);
        candidateLabels.append(label);
    }
    
    vbox->addLayout(hbox_upper);
    vbox->addLayout(hbox_lower);
    setLayout(vbox);
    
    pager = new SimplePager(candidateLabels, imePagerHint);
    pager->setCandidateCntPerPage(ImeWindow::candidateCountPerPage);
    
    installEventFilter(this);

    /* Initialize keyboard */
    keyboard = new NonStandardKeyboard;
    keyboard->initializeKeys();
    keyboard->setParentWindow(this);
    
    pinyinVocabulary_db->init1();
}

ImeWindow::~ImeWindow()
{
	delete keyboard;
	delete pinyinVocabulary_db;
    delete pager;
}

void ImeWindow::showCandidateOnBoard(QString &inputText)
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(this->keyboard);

    if (nsKeyboard->getKeyRole() != NonStandardKeyboard::KR_Chinese && 
        nsKeyboard->getKeyRole() != NonStandardKeyboard::KR_Punctuation) {
        qDebug() << "Under keyRole - " 
                  << nsKeyboard->getKeyRole() 
                  << ", no need to show candidate on board";                
        return;
    }
    
    /* @inputText is the key word to search in the Chinese Character database */
    QVector<QString> searchContent;

    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Chinese) {             
        auto _p = pinyinVocabulary_db->search1(inputText);
        if (_p == nullptr) {
			qDebug() << inputText << " not found";
            pager->reset();
            pager->clearHighlight();
            pager->clearText();
            return;
        } else {
            searchContent = *_p;
        }
    } else if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Punctuation) {
        for (int i = 0; i < simpleT9glb::key_punctuation_candidate.size(); i++) {
            searchContent.append(simpleT9glb::key_punctuation_candidate.at(i));
        }
    }

    pager->setContent(searchContent);
    pager->refreshCandidate();

    /* Init decoration */
    pager->clearHighlight();
    pager->labelHighlightAt(0);

    /* If not match any items in the database, just keep the old ones in the pager */

    /* If length of @inputText equals to 0, clear the pager */
    if (inputText.length() == 0) {
        pager->reset();
        pager->clearHighlight();
        pager->clearText();
    }
}

void ImeWindow::handleCandidateSelForward()
{    
    pager->forward();
}

void ImeWindow::handleCandidateSelBackward()
{
    pager->backward();
}

void ImeWindow::handleCandidateSelPageUp()
{
    pager->pageUp();
}

void ImeWindow::handleCandidateSelPageDown()
{
    pager->pageDown();
}

void ImeWindow::handleKeyRoleSwith()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(keyboard);
    QString keyRoleText;

    switch (nsKeyboard->getKeyRole()) {
        case NonStandardKeyboard::KR_Chinese:
        default:
            keyRoleText = simpleT9glb::key_role_type_chinese_text;
            break;
        case NonStandardKeyboard::KR_English:
            keyRoleText = simpleT9glb::key_role_type_english_text;
            break;
        case NonStandardKeyboard::KR_English_Capital:
            keyRoleText = simpleT9glb::key_role_type_english_capital_text;
            break;
		case NonStandardKeyboard::KR_Digit:
			keyRoleText = simpleT9glb::key_role_type_digit_text;
			break;
        case NonStandardKeyboard::KR_Punctuation:
            keyRoleText = simpleT9glb::key_role_type_punctuation_text;
			break;
    }

    imeModeSwitch->setText(keyRoleText);
    pager->reset();
	nsKeyboard->displayBufferStackClear();
	imePinyin->setText(0);

    /* Prepare pager content if any */
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Punctuation) {
        QVector<QString> _info;
        for (int i = 0; i < simpleT9glb::key_punctuation_candidate.size(); i++) {
            _info.append(simpleT9glb::key_punctuation_candidate.at(i));
        }
        pager->setContent(_info);
        pager->currSelected_set(0);		
    }

    pager->refreshCandidate();
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Chinese) {
        imePinyin->setText(QString(""));
    }
   
    /* Clear highlight */
    qDebug() << "pager->currSelected_get() " << pager->currSelected_get();
    pager->clearCurrHightlight();

    /* If input method is 'Punctuation' mode, make the first candidate as selected */
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Punctuation) {
        pager->labelHighlightAt(0);
    }
}

void ImeWindow::handleMultiPurposeKey(int key)
{
	qDebug() << "handleMultiPurposeKey";
    QString inputText = keyboard->handleKeyPress(key); 
    imePinyin->setText(inputText);
    
    qDebug() << "inputText - " << inputText;
    showCandidateOnBoard(inputText);
}

void ImeWindow::handleFunctionKey(int key)
{
	qDebug() << "handleFunctionKey";
    QString inputText = keyboard->handleKeyPress(key); 
    imePinyin->setText(inputText);

    if (key == Qt::Key_Backspace) {
        /* We only need to show candidates in case of Chinese or Punctuations selection */
        showCandidateOnBoard(inputText);
    }

    /* Press 'Space Key' mean confirm the current candidates 
     * selection and make it shown on parent input box */
    const NonStandardKeyboard *nsKeyboard = dynamic_cast<const NonStandardKeyboard *>(getKeyboard());
    int _keyRole = nsKeyboard->getKeyRole();

    QLineEdit *parentTextInput = dynamic_cast<QLineEdit *>(getParentWidget());
    
    if (key == Qt::Key_Space) {
        if (_keyRole == NonStandardKeyboard::KR_Punctuation) {
            parentTextInput->setText(parentTextInput->text() + pager->getCurrSelectedLabelText());            
        } else if (_keyRole == NonStandardKeyboard::KR_Chinese) {
            parentTextInput->setText(parentTextInput->text() + pager->getCurrSelectedLabelText());
            /* Reset keyboard buffer, pager, page hint and candidates */
            (const_cast<NonStandardKeyboard *>(nsKeyboard))->displayBufferStackClear();
            pager->reset();
            pager->clearHighlight();
            imePagerHint->setText("[0/0]");
            imePinyin->setText("");
        } else {
            /* English, English_Capital, Punctuation */
            parentTextInput->setText(parentTextInput->text() + getPinyinContent());
            (const_cast<NonStandardKeyboard *>(nsKeyboard))->displayBufferStackClear();
            imePinyin->setText("");
        }
    }
}

void ImeWindow::handleDigitKey(int key)
{
	qDebug() << "handleDigitKey";
    QString inputText = keyboard->handleKeyPress(key); 
    imePinyin->setText(inputText);
}

void ImeWindow::handleKeyPressEvent(int key)
{
	NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(keyboard);

	switch (nsKeyboard->getKeyRole()) {
	case NonStandardKeyboard::KR_Chinese:
		if (key >= simpleT9glb::multi_purpose_key_start && key <= simpleT9glb::multi_purpose_key_end) {
	        handleMultiPurposeKey(key);
	    } else {
	        handleFunctionKey(key);
	    }
        break;

    case NonStandardKeyboard::KR_English:        
    case NonStandardKeyboard::KR_English_Capital:
        if (key >= simpleT9glb::multi_purpose_key_start && key <= simpleT9glb::multi_purpose_key_end) {
	        handleMultiPurposeKey(key);
	    } else {
	        handleFunctionKey(key);
	    }
        break;

    case NonStandardKeyboard::KR_Digit:
        if (key >= simpleT9glb::digit_key_start && key <= simpleT9glb::digit_key_end) {
            handleDigitKey(key);
        } else {
            handleFunctionKey(key);
        }
        break;

    case NonStandardKeyboard::KR_Punctuation:
        handleFunctionKey(key);
        break;
        
	default:
	    break;
	}    
}

bool ImeWindow::eventFilter(QObject *obj, QEvent *event)
{
    (void)obj;
    
    if (event->type() == QEvent::KeyPress) {              
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		qDebug() << "Key - " << QString::number(keyEvent->key(), 16) << " pressed";
        handleKeyPressEvent(keyEvent->key());
    } else if (event->type() == QEvent::HoverEnter) {
		qDebug() << "Mouse Hover Enter";
    } else if (event->type() == QEvent::HoverLeave) {
		qDebug() << "Mouse Hover Leave";
    } else if (event->type() == QEvent::HoverMove) {
		qDebug() << "Mouse Hover Move";
    }

    return QObject::eventFilter(obj, event);
}

