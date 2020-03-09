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
#include <QPalette>
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

SimplePager::SimplePager(QVector<QLabel *> &labels, QLabel *hintLabel) :
    candidateLabels(labels),
    pagerHintLabel(hintLabel),
    currPage(0), 
    pageCount(0), 
    lastPageCharCount(0), 
    currSelected(0)
{

}

SimplePager::~SimplePager()
{
}

void SimplePager::preparePageContent()
{
    int pos = currPage * candidateCntPerPage;
    int count = (content.length() - pos < candidateCntPerPage) ? 
        content.length() - pos : candidateCntPerPage;
   
    contentOfCurrentPage.clear();

    for (int i = 0; i < count; i++) {
        contentOfCurrentPage.append(content.at(pos + i));
    }
}

void SimplePager::setContent(QVector<QString> info)
{
   this->content = info;
  
   if ((info.size() % candidateCntPerPage) != 0) {
       pageCount = (info.size() + candidateCntPerPage)/candidateCntPerPage;
       lastPageCharCount = (info.size() % candidateCntPerPage);
   } else {
       pageCount = info.size()/candidateCntPerPage;
       lastPageCharCount = candidateCntPerPage;
   }

   //std::cout << "info.size() - " << info.size() << ", candidateCntPerPage - " << candidateCntPerPage << std::endl;
   //std::cout << "setContent, pageCount - " << pageCount << std::endl;

   currPage = 0;

   preparePageContent();
}

int SimplePager::setCandidateCntPerPage(int count)
{
    candidateCntPerPage = count;
    return candidateCntPerPage;
}

QVector<QString> &SimplePager::getPageContent()
{
    return this->contentOfCurrentPage;
}

int SimplePager::getCandidateCountOfCurrPage() const
{
    if (pageCount == 1) {
        return lastPageCharCount;
    } else if (currPage < (pageCount - 1)) {
        return candidateCntPerPage;
    } else {
        return lastPageCharCount;
    }
}

void SimplePager::reset() 
{
    this->content.clear();
    this->contentOfCurrentPage.clear();

    currPage = 0;
    pageCount = 0;
    lastPageCharCount = 0;
    currSelected = 0;

    clearHighlight();
    clearText();
}

int SimplePager::currSelected_inc() 
{ 
    if (getCandidateCountOfCurrPage() > 0) {
        currSelected++;
        currSelected = currSelected > (getCandidateCountOfCurrPage() - 1) ? 0 : currSelected;
    }
    
    return currSelected;
}

int SimplePager::currSelected_dec() 
{ 
    if (getCandidateCountOfCurrPage() > 0) {
        currSelected--; 
        currSelected = currSelected < 0 ? (getCandidateCountOfCurrPage() - 1) : currSelected;
    }
    
    return currSelected;
}

int SimplePager::currSelected_set(int pos) 
{ 
    if (pos >= 0 && pos <= std::min(getCandidateCountOfCurrPage(), 
            (simpleT9glb::max_chinese_char_candidate_per_page - 1))) { 
        currSelected = pos; 
    } 

    return currSelected;
}

int SimplePager::currSelected_get()
{
    return currSelected;
}

void SimplePager::candidateLabelHighlight(QLabel *label, bool highlight)
{
    QPalette pal = label->palette();
    
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

void SimplePager::clearHighlight()
{
    for (auto &label : candidateLabels) {
        candidateLabelHighlight(label, false);
    }
}

void SimplePager::clearText()
{
    for (auto &label : candidateLabels) {
        label->setText("");
    }
}

void SimplePager::forward()
{
    QLabel *lastLabel = candidateLabels.at(currSelected_get());
    QLabel *currLabel = candidateLabels.at(currSelected_inc());
   
    if (getCandidateCountOfCurrPage() > 1) {
        candidateLabelHighlight(currLabel, true);
        candidateLabelHighlight(lastLabel, false);
    }
}

void SimplePager::backward()
{
    QLabel *lastLabel = candidateLabels.at(currSelected_get());
    QLabel *currLabel = candidateLabels.at(currSelected_dec());

    if (getCandidateCountOfCurrPage() > 1) {
        candidateLabelHighlight(currLabel, true);
        candidateLabelHighlight(lastLabel, false);
    }
}

void SimplePager::pageUp()
{
    if (currPage > 0)
        currPage--;
    
    preparePageContent();
    refreshCandidate();

    /* When page up/down, reset highlight character pos to the first one */
    if (currSelected_get() > 0) {
        QLabel *lastLabel = candidateLabels.at(currSelected_get());
        QLabel *currLabel = candidateLabels.at(currSelected_set(0));
        candidateLabelHighlight(currLabel, true);
        candidateLabelHighlight(lastLabel, false);
    }
}

void SimplePager::pageDown()
{
    if (currPage < (pageCount - 1))
        currPage++;

    preparePageContent();
    refreshCandidate();
    
    /* When page up/down, reset highlight character pos to the first one */
    if (currSelected_get() > 0) {
        QLabel *lastLabel = candidateLabels.at(currSelected_get());
        QLabel *currLabel = candidateLabels.at(currSelected_set(0));

        candidateLabelHighlight(currLabel, true);
        candidateLabelHighlight(lastLabel, false);
    }
}

int SimplePager::refreshCandidate()
{
    QVector<QString> pageContent = getPageContent();

    int page = ((pageContent.size() == 0) ? 0 : getCurrPageNatual());
    int pageCount = getPageCount();

    //imePagerHint->setText(QString("[%1/%2]").arg(page).arg(pageCount));
    pagerHintLabel->setText(QString("[%1/%2]").arg(page).arg(pageCount));
   
    for (auto iter = candidateLabels.begin(); iter != candidateLabels.end(); iter++) {
        (*iter)->setText("");
    }

    int i = 0;
    for (auto iter = pageContent.begin(); iter != pageContent.end(); iter++) {
		qDebug() << *iter;
        candidateLabels.at(i)->setText(*iter);
        i++;
    }
    
    return pageContent.size();    
}

QLabel *SimplePager::labelAt(int pos)
{
    if (pos < 0 || pos > (candidateLabels.size() - 1)) {
        return nullptr;
    }

    return candidateLabels.at(pos);
}

QString SimplePager::labelTextAt(int pos)
{
    QLabel *label = labelAt(pos);
   
    return label != nullptr ? label->text() : QString("");
}

QString SimplePager::getCurrSelectedLabelText()
{
    return labelTextAt(currSelected_get());
}

void SimplePager::labelHighlightAt(int pos, bool highlight)
{
    QLabel *label = labelAt(pos);

    if (label == nullptr) {
        return;
    }

    candidateLabelHighlight(label, highlight);
}

void SimplePager::clearCurrHightlight()
{
    QLabel *label = labelAt(currSelected_get());

    if (label == nullptr) {
        return;
    }

    candidateLabelHighlight(label, false);
}
