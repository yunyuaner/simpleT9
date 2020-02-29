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
    
    QString &getPageContent();
    //QString &getPageContent(int page);
    
    void setContent(QString &info);
    int setChnCharCntPerPage(int count);

    int getCurrPage() const { return currPage; };
    int getCurrPageNatual() const { return (currPage + 1); }
    int getPageCount() const { return pageCount; };

    void reset();

private:
    void PreparePageContent();

private:
    QVector<QChar> content;
    QString *pageContent;
    
    int currPage;
    int pageCount;
    int chnCharCntPerPage;
};

#endif /* _PAGER_H */
