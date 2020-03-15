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

namespace hycx {
namespace libsimpleT9 {

class SimplePager
{
public:
    SimplePager(QVector<QLabel *> &candidateLabels, QLabel *pagerHintLabel);
    virtual ~SimplePager();
    
    int setCandidateCntPerPage(int count);
    void setContent(QVector<QString> info);
    
    int refreshCandidate();
    
    void reset();
    
    void forward();
    void backward();
    void pageUp();
    void pageDown();
    
    int currSelected_inc(); 
    int currSelected_dec();
    int currSelected_set(int pos);
    int currSelected_get();
    
    void clearHighlight();
    void clearCurrHightlight();
    void labelHighlightAt(int pos, bool hightlight = true);
    
    void clearText();
    QString labelTextAt(int pos);
    QString getCurrSelectedLabelText();

private:
    QVector<QString> &getPageContent();
    int getCurrPage() const { return currPage; };
    int getCurrPageNatual() const { return (currPage + 1); }
    int getPageCount() const { return pageCount; };
    int getCandidateCountOfCurrPage() const;
    void candidateLabelHighlight(QLabel *label, bool highlight = true);
    QLabel *labelAt(int pos);
    void preparePageContent();
    
private:
    QVector<QString> content;
    QVector<QString> contentOfCurrentPage;
    QVector<QLabel *> &candidateLabels;
    QLabel *pagerHintLabel;
    
    int currPage;
    int pageCount;
    int candidateCntPerPage;
    int lastPageCharCount;
    int currSelected;   /* Currently selected candidate */
};

}} /* namespace */

#endif /* _PAGER_H */
