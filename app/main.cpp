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
 *  version 3 along with simpleT9; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QDebug>
#include "simpleT9.h"
#include "MainWindow.h"

using namespace hycx::simpleT9_sample_app;

#if 0
static void search_then_show(SimpleVocabulary &_vol, std::string to_search)
{
    QVector<QString> *results;
    int i = 0;
    
    results = _vol.search1(QString::fromStdString(to_search));
    
    if (results != nullptr) {
        for (auto iter = results->begin(); iter != results->end(); iter++) {
            std::cout << i++ << (*iter).toStdString() << std::endl;
        }
    }
}
#endif

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MainWindow *mainWindow = MainWindow::getInstance();
    mainWindow->resize(400, 300);
    mainWindow->show();
    return app.exec();   
#if 0    
    SimpleVocabulary vocabulary;
    vocabulary.init1();
    //vocabulary.show();
    //search_then_show(vocabulary, "guo");
    //search_then_show(vocabulary, "ma'ma");
    search_then_show(vocabulary, "zhou'jie'lu");
#endif
}
