#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Clock");
    w.setStyleSheet("background-color: white;");
    w.resize(1000, w.height()-40);
    w.show();
    return a.exec();
}
