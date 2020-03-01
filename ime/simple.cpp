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
#include <iostream>
#include <algorithm>
#include "simple.h"
#include "key.h"
#include "keyboard.h"
#include "pager.h"
#include "../data/fontlib_zh.h"
#include "../data/vocabulary.h"

//void messageBox(QString text)
//{
//    QMessageBox msgBox;
//    msgBox.setText(text);
//    msgBox.exec();
//}


MainWindow *MainWindow::_instance = nullptr;
int ImeWindow::chnCharCntPerPage = 6;
const char *ImeWindow::imeTitleStr = "华创拼音";

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

void MainWindow::handle__Key_O()
{
    QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
    textInput->setText(textInput->text() + currLabel->text());
}

void MainWindow::handle__Key_Return()
{
    imeWindow->close();
    imeWindowShown = false;
}

void MainWindow::handle__Key_Right()
{
    QLabel *lastLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
    QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_inc());

    imeWindow->ChnCharLabelHighlight(currLabel, true);
    imeWindow->ChnCharLabelHighlight(lastLabel, false);
}

void MainWindow::handle__Key_Left()
{
    QLabel *lastLabel = imeWindow->chnChars.at(imeWindow->currSelected_get());
    QLabel *currLabel = imeWindow->chnChars.at(imeWindow->currSelected_dec());

    imeWindow->ChnCharLabelHighlight(currLabel, true);
    imeWindow->ChnCharLabelHighlight(lastLabel, false);
}

void MainWindow::handle__Key_Up()
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

void MainWindow::handle__Key_Down()
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

void MainWindow::handle__Key_Role()
{
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(imeWindow->keyboard);
    QString keyRoleText;

    switch (nsKeyboard->getKeyRole()) {
        case NonStandardKeyboard::KR_Chinese:
        default:
            keyRoleText = "[中文]";
            break;
        case NonStandardKeyboard::KR_English:
            keyRoleText = "[英文小写]";
            break;
        case NonStandardKeyboard::KR_English_Capital:
            keyRoleText = "[英文大写]";
            break;
    }

    imeWindow->imeModeSwitch->setText(keyRoleText);
    imeWindow->pager.reset();
    imeWindow->refreshCandidate();
    imeWindow->imePinyin->setText(QString(""));
   
    /* Clear highlight */
    QLabel *label = imeWindow->chnChars.at(imeWindow->currSelected_get());
    imeWindow->ChnCharLabelHighlight(label, false);
}

void MainWindow::handleMultiPurposeKey(int key)
{
    std::cout << "handleMultiPurposeKey" << std::endl;
    QString &inputText = imeWindow->keyboard->handleKeyPress(key); 
    imeWindow->imePinyin->setText(inputText);
    
    std::cout << "inputText - " << inputText.toStdString() << std::endl;
    
    NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(imeWindow->keyboard);
    if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Chinese) {
        imeWindow->showPinyinOnBoard(inputText);
    }
}

void MainWindow::handleFunctionKey(int key)
{
    std::cout << "handleFunctionKey" << std::endl;
    QString &inputText = imeWindow->keyboard->handleKeyPress(key); 
    imeWindow->imePinyin->setText(inputText);

    if (key == Qt::Key_Backspace) {
        NonStandardKeyboard *nsKeyboard = dynamic_cast<NonStandardKeyboard *>(imeWindow->keyboard);
        if (nsKeyboard->getKeyRole() == NonStandardKeyboard::KR_Chinese) {
            imeWindow->showPinyinOnBoard(inputText);
        }
    }
}

void MainWindow::handleKeyPressEvent(int key)
{
    if (key >= Qt::Key_1 && key <= Qt::Key_8) {
        handleMultiPurposeKey(key);
    } else {
        handleFunctionKey(key);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() & Qt::LeftButton) {
            
            if (static_cast<QLineEdit *>(obj) == textInput && !imeWindowShown) {            
                QPoint globalCursorPos = QCursor::pos();
                
                imeWindow->resize(250, 150);
                imeWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
                imeWindow->setGeometry(globalCursorPos.x() + 10, globalCursorPos.y() + 10, 400, 20);
                imeWindow->show();      
                imeWindowShown = true;          
            }
        }        
    } else if (event->type() == QEvent::KeyPress) {              
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        //messageBox(QString::number(keyEvent->key(), 16));  
        /*
        if (keyEvent->key() == Qt::Key_Return) {
            handle__Key_Return(); 
        } else if (keyEvent->key() == Qt::Key_O) {
            handle__Key_O();
        } else if (keyEvent->key() == Qt::Key_Up) {
            handle__Key_Up();
        } else if (keyEvent->key() == Qt::Key_Down) {
            handle__Key_Down();
        } else if (keyEvent->key() >= Qt::Key_1 && keyEvent->key() <= Qt::Key_8) {
            handle__Key_Digit(keyEvent->key());
        } else {
            handleGeneric(keyEvent->key());
        }
        */
        std::cout << "Key - " << QString::number(keyEvent->key(), 16).toStdString() << " pressed" << std::endl;
        handleKeyPressEvent(keyEvent->key());
    } else {
        // Standard event processing
        return QObject::eventFilter(obj, event);
    }

    return true;
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

    std::cout << "44" << std::endl;
    
    int i = 0;
    for (auto iter = pageContent.begin(); iter != pageContent.end(); iter++) {
        std::cout << (*iter).toStdString() << std::endl;
        chnChars.at(i)->setText(*iter);
        i++;
    }
    
    std::cout << "55" << std::endl;
    
    return pageContent.size();
}

ImeWindow::ImeWindow(QWidget *parent) : 
    QDialog(parent), 
    currSelected(0), 
    currPage(0), 
    pageCount(0),
    pinyinSingleWord_db(hycx::wuhan::simpleT9::init_db()),
    pinyinVocabulary_db(new Vocabulary)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox_upper = new QHBoxLayout();
    QHBoxLayout *hbox_lower = new QHBoxLayout();
    
    imeTitle = new QLabel(QString::fromUtf8(reinterpret_cast<const char *>(ImeWindow::imeTitleStr)));
    imePinyin = new QLabel("");
    imePinyinVar = new QLabel("");
    hbox_upper->addWidget(imeTitle);
    hbox_upper->addWidget(imePinyin);
    hbox_upper->addWidget(imePinyinVar);
  
    imeModeSwitch = new QLabel("[中文]");
    imePagerHint = new QLabel("[0/0]");
    hbox_lower->addWidget(imeModeSwitch);
    hbox_lower->addWidget(imePagerHint);

    pager.setChnCharCntPerPage(ImeWindow::chnCharCntPerPage);

    for (int i = 0; i < ImeWindow::chnCharCntPerPage; i++) {
        //QLabel *label = new QLabel(pageContent.at(i));
        QLabel *label = new QLabel("");
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        //ChnCharLabelHighlight(label, (i == currSelected_get()));
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
    pinyinVocabulary_db->init();
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
    currSelected++;
    currSelected = currSelected > (ImeWindow::chnCharCntPerPage - 1) ? 0 : currSelected;
    
    return currSelected;
}

int ImeWindow::currSelected_dec() 
{ 
    currSelected--; 
    currSelected = currSelected < 0 ? (ImeWindow::chnCharCntPerPage - 1) : currSelected;
    
    return currSelected;
}

int ImeWindow::currSelected_set(int pos) 
{ 
    if (pos >= 0 && pos <=5) { 
        currSelected = pos; 
    } 

    return currSelected;
}

int ImeWindow::currSelected_get()
{
    return currSelected;
}

void ImeWindow::showPinyinOnBoard(QString &inputText)
{
    /* @inputText is the key word to search in the Chinese Character database */
    QVector<QString> searchContent;
    QString pinyinCandidate;
    
    if (inputText.indexOf("'") != -1) {
        std::cout << "Search in vocabulary database" << std::endl;
        
        auto _p = pinyinVocabulary_db->search(inputText);
        if (_p == nullptr) {
            std::cout << inputText.toStdString() << " not found" << std::endl;
            return;
        } else {
            searchContent = *_p;
        }
    } else {
        std::cout << "Search in single word database" << std::endl;
        
        QHash<QString, QString>::const_iterator iter = pinyinSingleWord_db->find(inputText);
        if (iter == pinyinSingleWord_db->cend()) {
            std::cout << inputText.toStdString() << " not found" << std::endl;
            return;
        } else {
            pinyinCandidate = static_cast<QString>(*iter);
            std::cout << "pinyinCandidate - " << pinyinCandidate.toStdString() << std::endl;
        
            for (auto iter = pinyinCandidate.begin(); iter != pinyinCandidate.end(); iter++) {
                searchContent.append(*iter);
            }
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

    /* If not match any items in the database, just key the old ones in the pager */

    /* If length of @inputText equals to 0, clear the pager */
    if (inputText.length() == 0) {
        pager.reset();
        for (auto iter = chnChars.begin(); iter != chnChars.end(); iter++) {
            (*iter)->setText(0);
            ChnCharLabelHighlight(*iter, false);
        }
    }
}
