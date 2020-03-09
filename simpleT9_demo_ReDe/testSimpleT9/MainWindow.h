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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    virtual ~MainWindow() {};   
    static MainWindow *getInstance(); 

private:
    explicit MainWindow(QWidget *parent = nullptr);
    
private:
    QLineEdit *textInput;
    SimpleT9 simpleT9;

private slots:

private:
    static MainWindow *_instance;
    bool imeWindowShown;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
