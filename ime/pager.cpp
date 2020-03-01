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
   } else {
       pageCount = info.size()/chnCharCntPerPage;
   }

   //std::cout << "info.size() - " << info.size() << ", chnCharCntPerPage - " << chnCharCntPerPage << std::endl;
   //std::cout << "setContent, pageCount - " << pageCount << std::endl;

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
    currPage(0), pageCount(0)
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

void SimplePager::reset() 
{
    //if (pageContent != nullptr && pageContent->size() > 0) {
    //    pageContent->clear();
    //}

    this->content.clear();
    this->contentOfCurrentPage.clear();

    currPage = 0;
    pageCount = 0;
}
