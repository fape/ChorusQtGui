#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("fape");
    QCoreApplication::setOrganizationDomain("fape.hu");
    QCoreApplication::setApplicationName("ChorusQtGui");
    MainWindow w;
    w.show();

    return a.exec();
}
