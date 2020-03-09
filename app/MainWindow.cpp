#include "MainWindow.h"

MainWindow *MainWindow::_instance = nullptr;

MainWindow::MainWindow(QWidget *parent) : 
    QWidget(parent), 
    textInput(new QLineEdit), 
    imeWindowShown(false)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    textInput = new QLineEdit;
    textInput->setPlaceholderText("Input text here");
    vbox->addWidget(textInput);
    setLayout(vbox);

    installEventFilter(this);
    textInput->installEventFilter(this);

    simpleT9.attachParentWidget(textInput);
}

MainWindow *MainWindow::getInstance() 
{
    if (_instance == nullptr) {
        _instance = new MainWindow;
    }

    return _instance;
};

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (this->textInput->hasFocus()) {
        if (event->type() == QEvent::KeyPress && static_cast<QLineEdit *>(obj) == textInput) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Backspace) {
                /* TODO: Actually we should derive a subclass from QTextInput
                 * and override its 'event' method, so as to make it only 
                 * reponse to 'Backspace' key and ignore others. Since it's 
                 * simple demo here, I'm not planning to do it here.*/
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            qDebug() << "QEvent::MouseButtonPress";
            
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() & Qt::LeftButton) {                
                if (static_cast<QLineEdit *>(obj) == textInput && !imeWindowShown) {            
                    simpleT9.uiOpen();
                    imeWindowShown = true;
                }
            }        
        }
    } else if (imeWindowShown) {
        simpleT9.forwardEvent(event);   /* Forward Event to IME window */
    }
    
    return QObject::eventFilter(obj, event);
}
