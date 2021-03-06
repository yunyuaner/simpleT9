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

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QDebug>
#include "simpleT9.h"
#include "MainWindow.h"

using hycx::libsimpleT9::SimpleT9;
using hycx::libsimpleT9::SimpleWidget;

namespace hycx {
namespace simpleT9_sample_app {

class MyLineEidt;

MainWindow *MainWindow::_instance = nullptr;

MainWindow::MainWindow(QWidget *parent) : 
    QWidget(parent), 
    textInput(new MyLineEdit), 
    imeWindowShown(false)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    textInput->setPlaceholderText("Input text here");
    vbox->addWidget(textInput);
    setLayout(vbox);

    installEventFilter(this);
    textInput->installEventFilter(this);

    simpleT9.attachParentWidget(textInput);
}

MainWindow *MainWindow::getInstance() 
{
    if (_instance == nullptr) {
        _instance = new MainWindow;
    }

    return _instance;
};

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (this->textInput->hasFocus()) {
        if (event->type() == QEvent::KeyPress && static_cast<QLineEdit *>(obj) == textInput) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Backspace) {
                /* TODO: Actually we should derive a subclass from QTextInput
                 * and override its 'event' method, so as to make it only 
                 * reponse to 'Backspace' key and ignore others. Since it's 
                 * simple demo here, I'm not planning to do it here.*/
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            qDebug() << "QEvent::MouseButtonPress";
            
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() & Qt::LeftButton) {                
                if (static_cast<QLineEdit *>(obj) == textInput && !imeWindowShown) {            
                    simpleT9.uiOpen();
                    imeWindowShown = true;
                }
            }        
        }
    } else if (imeWindowShown) {
        simpleT9.forwardEvent(event);   /* Forward Event to IME window */
    }
    
    return QObject::eventFilter(obj, event);
}

MyLineEdit::MyLineEdit(const QString &contents, QWidget *parent) : QLineEdit(contents, parent)
{
}

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
}

MyLineEdit::~MyLineEdit()
{
}

void MyLineEdit::__setText(const QString &_text)
{
	this->QLineEdit::setText(_text);
}

QString MyLineEdit::__text() const
{
	return this->QLineEdit::text();
}

}} /* namespace */
