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

#ifndef _SIMPLET9_H
#define _SIMPLET9_H

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

namespace hycx {
namespace libsimpleT9 {

class SimpleWidget;

class SimpleT9 final
{
public:
    explicit SimpleT9();
    ~SimpleT9();

    void uiCreate();
    void uiDestroy();
    void uiOpen();
    void uiClose();

    std::string getOutput();

    bool forwardEvent(QEvent *event);
    void attachParentWidget(SimpleWidget *_parentWidget);

private:
    ImeWindow *imeWindow;    
};

class SimpleWidget
{
public:
	SimpleWidget();
	virtual ~SimpleWidget();

	virtual void __setText(const QString &_text);
	virtual QString __text() const;
};

}} /* namespace */

#endif /* _SIMPLET9_H */
