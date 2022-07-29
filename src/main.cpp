#include "inc/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QApplication::setOrganizationName("Specte Org");
    QApplication::setApplicationName("Timer");

    w.show();
    return a.exec();
}
