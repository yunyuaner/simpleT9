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
#include <QMouseEvent>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>

#include <iostream>
#include <algorithm>
#include "ui.h"
#include "key.h"
#include "keyboard.h"
#include "pager.h"
#include "../data/vocabulary.h"
#include "globals.h"

MainWindow *MainWindow::_instance = nullptr;

int ImeWindow::chnCharCntPerPage = simpleT9glb::max_chinese_char_candidate_per_page;
const char *ImeWindow::imeTitleStr = simpleT9glb::ime_title_string;

MainWindow::MainWindow(QWidget *parent) : 
    QWidget(parent), 
    textInput(new QLineEdit), 
    imeWindow(new ImeWindow(this)), 
    imeWindowShown(false)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    textInput = new QLineEdit;
    textInput->setPlaceholderText("Input text here");
    vbox->addWidget(textInput);
    setLayout(vbox);
    textInput->installEventFilter(this);
    imeWindow->installEventFilter(this);     
}

MainWindow *MainWindow::getInstance() 
{
    if (_instance == nullptr) {
        _instance = new MainWindow;
    }

    return _instance;
};

void MainWindow::handleCandidateSelForward()
{
    QLabel *lastLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
    QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_inc());

    if (imeWindow->pager.getCharCountOfCurrPage() > 1) {
        imeWindow->ChnCharLabelHighlight(currLabel, true);
        imeWindow->ChnCharLabelHighlight(lastLabel, false);
    }
}

void MainWindow::handleCandidateSelBackward()
{
    QLabel *lastLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
    QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_dec());

    if (imeWindow->pager.getCharCountOfCurrPage() > 1) {
        imeWindow->ChnCharLabelHighlight(currLabel, true);
        imeWindow->ChnCharLabelHighlight(lastLabel, false);
    }
}

void MainWindow::handleCandidateSelPageUp()
{
    imeWindow->pager.pageBackward();
    imeWindow->refreshCandidate();

    /* When page up/down, reset highlight character pos to the first one */
    if (imeWindow->currSelected_get() > 0) {
        QLabel *lastLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
        QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_set(0));

        imeWindow->ChnCharLabelHighlight(currLabel, true);
        imeWindow->ChnCharLabelHighlight(lastLabel, false);
    }
}

void MainWindow::handleCandidateSelPageDown()
{
    imeWindow->pager.pageForward();
    imeWindow->refreshCandidate();
    
    /* When page up/down, reset highlight character pos to the first one */
    if (imeWindow->currSelected_get() > 0) {
        QLabel *lastLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
        QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_set(0));

        imeWindow->ChnCharLabelHighlight(currLabel, true);
        imeWindow->ChnCharLabelHighlight(lastLabel, false);
    }
}

void MainWindow::handleKeyRoleSwith()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(imeWindow->keyboard);
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

    imeWindow->imeModeSwitch->setText(keyRoleText);
    imeWindow->pager.reset();
	nsKeyboard->displayBufferStackClear();
	imeWindow->imePinyin->setText(0);

    /* Prepare pager content if any */
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Punctuation) {
        QVector<QString> _info;
        for (int i = 0; i < simpleT9glb::key_punctuation_candidate.size(); i++) {
            _info.append(simpleT9glb::key_punctuation_candidate.at(i));
        }
        imeWindow->pager.setContent(_info);
        imeWindow->currSelected_set(0);		
    }

    imeWindow->refreshCandidate();
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Chinese) {
        imeWindow->imePinyin->setText(QString(""));
    }
   
    /* Clear highlight */
    QLabel *label = imeWindow->chnChars.at(imeWindow->currSelected_get());
    imeWindow->ChnCharLabelHighlight(label, false);

    /* If input method is 'Punctuation' mode, make the first candidate as selected */
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Punctuation) {
        QLabel *label = imeWindow->chnChars.at(0);
        imeWindow->ChnCharLabelHighlight(label, true);
    }
}

void MainWindow::handleMultiPurposeKey(int key)
{
	qDebug() << "handleMultiPurposeKey";
    QString inputText = imeWindow->keyboard->handleKeyPress(key); 
    imeWindow->imePinyin->setText(inputText);
    
    std::cout << "inputText - " << inputText.toStdString() << std::endl;
    imeWindow->showCandidateOnBoard(inputText);
}

void MainWindow::handleFunctionKey(int key)
{
	qDebug() << "handleFunctionKey";
    QString inputText = imeWindow->keyboard->handleKeyPress(key); 
    imeWindow->imePinyin->setText(inputText);

    if (key == Qt::Key_Backspace) {
        /* We only need to show candidates in case of Chinese or Punctuations selection */
        imeWindow->showCandidateOnBoard(inputText);
    }

    /* Press 'Space Key' mean confirm the current candidates 
     * selection and make it shown on parent input box */
    const NonStandardKeyboard *nsKeyboard = dynamic_cast<const NonStandardKeyboard *>(imeWindow->getKeyboard());
    int _keyRole = nsKeyboard->getKeyRole();
    
    if (key == Qt::Key_Space) {
        if (_keyRole == NonStandardKeyboard::KR_Punctuation) {
            QLabel *label = imeWindow->chnChars.at(imeWindow->currSelected_get());
            this->textInput->setText(this->textInput->text() + label->text());            
        } else if (_keyRole == NonStandardKeyboard::KR_Chinese) {
            QLabel *label = imeWindow->chnChars.at(imeWindow->currSelected_get());
            this->textInput->setText(this->textInput->text() + label->text());

            /* Reset keyboard buffer, pager, page hint and candidates */
            (const_cast<NonStandardKeyboard *>(nsKeyboard))->displayBufferStackClear();
            imeWindow->pager.reset();
            imeWindow->imePagerHint->setText("[0/0]");
            imeWindow->imePinyin->setText("");
            for (auto &label : imeWindow->chnChars) {
                label->setText("");
                imeWindow->ChnCharLabelHighlight(label, false);
            }

            imeWindow->currPage = 0;
            imeWindow->pageCount = 0;
            imeWindow->currSelected = 0;
        } else {
            /* English, English_Capital, Punctuation */
            this->textInput->setText(this->textInput->text() + imeWindow->getPinyinContent());
            (const_cast<NonStandardKeyboard *>(nsKeyboard))->displayBufferStackClear();
            imeWindow->imePinyin->setText("");
        }
    }
}

void MainWindow::handleDigitKey(int key)
{
	qDebug() << "handleDigitKey";
    QString inputText = imeWindow->keyboard->handleKeyPress(key); 
    imeWindow->imePinyin->setText(inputText);
}

void MainWindow::handleKeyPressEvent(int key)
{
	NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(imeWindow->keyboard);

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

void MainWindow::eventFilterForIMEWindow(QObject *obj, QEvent *event)
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
}

void MainWindow::eventFilterForMainWindow(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress && static_cast<QLineEdit *>(obj) == textInput) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Backspace) {
            /* TODO: Actually we should derive a subclass from QTextInput
             * and override its 'event' method, so as to make it only 
             * reponse to 'Backspace' key and ignore others. Since it's 
             * simple demo here, I'm not planning to do it here.*/
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() & Qt::LeftButton) {
            
            if (static_cast<QLineEdit *>(obj) == textInput && !imeWindowShown) {            
                QPoint globalCursorPos = QCursor::pos();
                
                imeWindow->resize(250, 150);
                imeWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
                //imeWindow->setFixedSize(imeWindow->size());
                imeWindow->setGeometry(globalCursorPos.x() + 10, globalCursorPos.y() + 10, 400, 20);
                imeWindow->show();      
                imeWindowShown = true;          
            }
        }        
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (this->textInput->hasFocus()) {
        eventFilterForMainWindow(obj, event);
    } else {
        eventFilterForIMEWindow(obj, event);
    }

    // Standard event processing
    return QObject::eventFilter(obj, event);
}

int ImeWindow::refreshCandidate()
{
    //QString &pageContent = pager.getPageContent();
    QVector<QString> pageContent = pager.getPageContent();

    int page = ((pageContent.size() == 0) ? 0 : pager.getCurrPageNatual());
    int pageCount = pager.getPageCount();

    imePagerHint->setText(QString("[%1/%2]").arg(page).arg(pageCount));
   
    for (auto iter = chnChars.begin(); iter != chnChars.end(); iter++) {
        (*iter)->setText("");
    }

    //for (int i = 0; i < pageContent.length(); i++) {
    //    chnChars.at(i)->setText(pageContent.at(i));
    //}

    int i = 0;
    for (auto iter = pageContent.begin(); iter != pageContent.end(); iter++) {
        //std::cout << (*iter).toStdString() << std::endl;
		qDebug() << *iter;
        chnChars.at(i)->setText(*iter);
        i++;
    }
    
    return pageContent.size();
}

ImeWindow::ImeWindow(QWidget *parent) : 
    QDialog(parent), 
    currSelected(0), 
    currPage(0), 
    pageCount(0),
    pinyinVocabulary_db(new SimpleVocabulary)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox_upper = new QHBoxLayout();
    QHBoxLayout *hbox_lower = new QHBoxLayout();
    
    imeTitle = new QLabel(QString::fromUtf8(reinterpret_cast<const char *>(ImeWindow::imeTitleStr)));
    imePinyin = new QLabel("");
    //imePinyinVar = new QLabel("");
    hbox_upper->addWidget(imeTitle);
    hbox_upper->addWidget(imePinyin);
    //hbox_upper->addWidget(imePinyinVar);
  
    imeModeSwitch = new QLabel(simpleT9glb::key_role_type_chinese_text);
    imePagerHint = new QLabel("[0/0]");
    hbox_lower->addWidget(imeModeSwitch);
    hbox_lower->addWidget(imePagerHint);

    pager.setChnCharCntPerPage(ImeWindow::chnCharCntPerPage);

    for (int i = 0; i < ImeWindow::chnCharCntPerPage; i++) {
        QLabel *label = new QLabel("");
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        ChnCharLabelHighlight(label, false);
        hbox_lower->addWidget(label);
        chnChars.append(label);
    }

    vbox->addLayout(hbox_upper);
    vbox->addLayout(hbox_lower);
    setLayout(vbox);

    /* Initialize keyboard */
    keyboard = new NonStandardKeyboard;
    keyboard->initializeKeys();

    /* May use lazy-initialization */
    //pinyinVocabulary_db->init();
    pinyinVocabulary_db->init1();
}

ImeWindow::~ImeWindow()
{
	delete keyboard;
	delete pinyinVocabulary_db;
}

void ImeWindow::ChnCharLabelHighlight(QLabel *label, bool highlight = true)
{
    QPalette pal = palette();
    
    if (highlight) {
        pal.setColor(QPalette::Background, Qt::black);
        pal.setColor(QPalette::WindowText, Qt::white);
    } else {
        pal.setColor(QPalette::Background, Qt::white);
        pal.setColor(QPalette::WindowText, Qt::black);
    }
    
    label->setAutoFillBackground(true);
    label->setPalette(pal);
}

int ImeWindow::currSelected_inc() 
{ 
    if (pager.getCharCountOfCurrPage() > 0) {
        currSelected++;
        currSelected = currSelected > (pager.getCharCountOfCurrPage() - 1) ? 0 : currSelected;
    }
    
    return currSelected;
}

int ImeWindow::currSelected_dec() 
{ 
    if (pager.getCharCountOfCurrPage() > 0) {
        currSelected--; 
        currSelected = currSelected < 0 ? (pager.getCharCountOfCurrPage() - 1) : currSelected;
    }
    
    return currSelected;
}

int ImeWindow::currSelected_set(int pos) 
{ 
    if (pos >= 0 && pos <= std::min(pager.getCharCountOfCurrPage(), 
            (simpleT9glb::max_chinese_char_candidate_per_page - 1))) { 
        currSelected = pos; 
    } 

    return currSelected;
}

int ImeWindow::currSelected_get()
{
    return currSelected;
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
            return;
        } else {
            searchContent = *_p;
        }
    } else if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Punctuation) {
        for (int i = 0; i < simpleT9glb::key_punctuation_candidate.size(); i++) {
            searchContent.append(simpleT9glb::key_punctuation_candidate.at(i));
        }
    }

    pager.setContent(searchContent);
    refreshCandidate();

    /* Init decoration */
    QLabel *a_label;
    for (auto iter = chnChars.begin(); iter != chnChars.end(); iter++) {
        a_label = *iter;
        ChnCharLabelHighlight(a_label, false);
    }
    
    a_label = chnChars[0];
    ChnCharLabelHighlight(a_label, true);

    /* If not match any items in the database, just keep the old ones in the pager */

    /* If length of @inputText equals to 0, clear the pager */
    if (inputText.length() == 0) {
        pager.reset();
        for (auto iter = chnChars.begin(); iter != chnChars.end(); iter++) {
            (*iter)->setText(0);
            ChnCharLabelHighlight(*iter, false);
        }
    }
}
