#include "mainwindow.h"
#include "startupdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startupdialog *dialog = new startupdialog;
    dialog->show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
