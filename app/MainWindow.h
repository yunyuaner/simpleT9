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
#include "ui.h"
#include "simpleT9.h"

/**
 * Requirements on your 'Edit Box Control'
 * 
 * (1) Define your own 'Edit Box Control' Widget class, say 'MyLineEdit', which should 
 *     multi-inheritate class SimpleWidget and a QT's built-in 'Edit Box Control',
 *     e.g., QLineEdit
 * 
 * (2) Implement __setText and __text virtual functions, which should be served as 
 *     setter and getter of your 'Edit Box Control'
 *
 * (3) Use class MyLineEdit at the place where an 'Edit Box Control' is required
 *
 **/

class MyLineEdit : public SimpleWidget, public QLineEdit 
{
public:
	MyLineEdit(const QString &contents, QWidget *parent = nullptr);
	MyLineEdit(QWidget *parent = nullptr);
	virtual ~MyLineEdit();

	virtual void __setText(const QString &_text);
	virtual QString __text() const;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    virtual ~MainWindow() {};   
    static MainWindow *getInstance(); 

private:
    explicit MainWindow(QWidget *parent = nullptr);
    
private:
    MyLineEdit *textInput;
    SimpleT9 simpleT9;

private slots:

private:
    static MainWindow *_instance;
    bool imeWindowShown;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
