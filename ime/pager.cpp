#include "pager.h"
#include <iostream>

void SimplePager::PreparePageContent()
{
    int pos = currPage * chnCharCntPerPage;
    int count = (content.length() - pos < chnCharCntPerPage) ? 
        content.length() - pos : chnCharCntPerPage;
   
    if (pageContent != nullptr) {
        delete pageContent;
        pageContent = nullptr;
    }

    pageContent = new QString;

    for (int i = 0; i < count; i++) {
        pageContent->append(content.at(pos + i));
    }
}

void SimplePager::setContent(QString &info)
{
    content.clear();

    QString::iterator iter;
    
    for (iter = info.begin(); iter != info.end(); iter++)
        content.append(*iter);

    currPage = 0;
    pageCount = (info.length() % chnCharCntPerPage) > 0 ? 
        ((info.length() + chnCharCntPerPage) / chnCharCntPerPage) : 
        (info.length() / chnCharCntPerPage);

   PreparePageContent(); 
}

int SimplePager::pageForward()
{
    if (currPage < (pageCount - 1))
        currPage++;

    PreparePageContent();

    return currPage;
}

int SimplePager::pageBackward()
{
    if (currPage > 0)
        currPage--;
    
    PreparePageContent();

    return currPage;
}

SimplePager::SimplePager() : 
    pageContent(nullptr), currPage(0), pageCount(0)
{

}

SimplePager::~SimplePager()
{
    if (pageContent != nullptr)
        delete pageContent;
}

int SimplePager::setChnCharCntPerPage(int count)
{
    chnCharCntPerPage = count;
    return chnCharCntPerPage;
}

QString &SimplePager::getPageContent()
{
    return *pageContent;
}

void SimplePager::reset() 
{
    if (pageContent != nullptr && pageContent->size() > 0) {
        pageContent->clear();
    }
    
    currPage = 0;
    pageCount = 0;
}
