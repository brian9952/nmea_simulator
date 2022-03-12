#include "mainwindow.h"
#include "startupdialog.h"
#include "aamdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //startupdialog *dialog = new startupdialog;
    //dialog->show();
    //AAMDialog *dialog = new AAMDialog;
    //dialog->show();

    MainWindow *w = new MainWindow;
    w->show();
    return a.exec();
}
