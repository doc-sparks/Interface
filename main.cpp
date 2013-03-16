#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // create the basic application
    QApplication a(argc, argv);

    // create the window
    MainWindow w;
    w.show();
    
    return a.exec();
}
