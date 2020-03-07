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

#ifndef _PAGER_H
#define _PAGER_H

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

class SimplePager
{
public:
    SimplePager();
    virtual ~SimplePager();
    
    int pageForward();
    int pageBackward();
    
    QVector<QString> &getPageContent();
    //QString &getPageContent(int page);
    
    void setContent(QVector<QString> info);
    int setChnCharCntPerPage(int count);

    int getCurrPage() const { return currPage; };
    int getCurrPageNatual() const { return (currPage + 1); }
    int getPageCount() const { return pageCount; };
    int getCharCountOfCurrPage() const;

    void reset();

private:
    void preparePageContent();
    
private:
    QVector<QString> content;
    QVector<QString> contentOfCurrentPage;
    //QString *pageContent;
    
    int currPage;
    int pageCount;
    int chnCharCntPerPage;
    int lastPageCharCount;
};

#endif /* _PAGER_H */
