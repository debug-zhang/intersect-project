#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    try{
        w.show();
        return a.exec();
    }catch (exception &e){
        QMessageBox::information(NULL, "出现异常", e.what());
        return 0;
    }
}
