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
#include <QDebug>

#include "pager.h"
#include <iostream>

void SimplePager::preparePageContent()
{
    int pos = currPage * chnCharCntPerPage;
    int count = (content.length() - pos < chnCharCntPerPage) ? 
        content.length() - pos : chnCharCntPerPage;
   
    contentOfCurrentPage.clear();

    for (int i = 0; i < count; i++) {
        contentOfCurrentPage.append(content.at(pos + i));
    }
}

void SimplePager::setContent(QVector<QString> info)
{
   this->content = info;
  
   if ((info.size() % chnCharCntPerPage) != 0) {
       pageCount = (info.size() + chnCharCntPerPage)/chnCharCntPerPage;
       lastPageCharCount = (info.size() % chnCharCntPerPage);
   } else {
       pageCount = info.size()/chnCharCntPerPage;
       lastPageCharCount = chnCharCntPerPage;
   }

   //std::cout << "info.size() - " << info.size() << ", chnCharCntPerPage - " << chnCharCntPerPage << std::endl;
   //std::cout << "setContent, pageCount - " << pageCount << std::endl;

   currPage = 0;

   preparePageContent();
}

int SimplePager::pageForward()
{
    if (currPage < (pageCount - 1))
        currPage++;

    preparePageContent();

    return currPage;
}

int SimplePager::pageBackward()
{
    if (currPage > 0)
        currPage--;
    
    preparePageContent();

    return currPage;
}

SimplePager::SimplePager() : 
    currPage(0), pageCount(0), lastPageCharCount(0)
{

}

SimplePager::~SimplePager()
{
    //if (pageContent != nullptr)
    //    delete pageContent;
}

int SimplePager::setChnCharCntPerPage(int count)
{
    chnCharCntPerPage = count;
    return chnCharCntPerPage;
}

QVector<QString> &SimplePager::getPageContent()
{
    //return this->content;
    return this->contentOfCurrentPage;
}

int SimplePager::getCharCountOfCurrPage() const
{
    if (pageCount == 1) {
        return lastPageCharCount;
    } else if (currPage < (pageCount - 1)) {
        return chnCharCntPerPage;
    } else {
        return lastPageCharCount;
    }
}

void SimplePager::reset() 
{
    //if (pageContent != nullptr && pageContent->size() > 0) {
    //    pageContent->clear();
    //}

    this->content.clear();
    this->contentOfCurrentPage.clear();

    currPage = 0;
    pageCount = 0;
    lastPageCharCount = 0;
}
