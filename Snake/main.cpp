#include "mainwindow.h"
#include <c++/ctime>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainWindow w;
   // w.show();
    w.showFullScreen();

    return a.exec();
}
