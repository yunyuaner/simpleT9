/*****************************************
 * Copyright (c) All Right Reserved
 * Shang Hai Hua Yuan Chuang Xin Co., Ltd
 * 
 * Author: Jia Guo <jiag@ntesec.com.cn>
 * Date:   Mar. 3rd 2020
 *
 *****************************************/
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include "ui.h"
#include "../data/vocabulary.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow *mainWindow = MainWindow::getInstance();

    mainWindow->resize(400, 300);
    mainWindow->setWindowTitle("Simple Text Input Demo");
    mainWindow->show();

    return app.exec();
    
    //Vocabulary vocabulary;
    //vocabulary.init();
    //vocabulary.search("ba'ba");
}
