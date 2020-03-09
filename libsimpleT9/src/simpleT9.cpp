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
 
#include "simpleT9.h"

SimpleT9::SimpleT9(): imeWindow(new ImeWindow)
{
}

SimpleT9::~SimpleT9()
{
    delete this->imeWindow;
}

void SimpleT9::uiCreate()
{
}

void SimpleT9::uiDestroy()
{
}

void SimpleT9::uiOpen()
{
    QPoint globalCursorPos = QCursor::pos();
                
    imeWindow->resize(250, 150);
    imeWindow->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    imeWindow->setGeometry(globalCursorPos.x() + 10, globalCursorPos.y() + 10, 400, 20);
    imeWindow->show();      
}

void SimpleT9::uiClose()
{
}

std::string SimpleT9::getOutput()
{
    return std::string("");
}

bool SimpleT9::forwardEvent(QEvent *event)
{
    return QApplication::sendEvent(imeWindow, event);
}

void SimpleT9::attachParentWidget(QWidget *_parentWidget)
{
    imeWindow->setParentWidget(_parentWidget);
}
