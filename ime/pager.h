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
