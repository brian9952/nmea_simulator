#include <mainwindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QFile file("../libs/stylesheets/VisualScript.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    QApplication a(argc, argv);
    a.setStyleSheet(styleSheet);
    MainWindow *w = new MainWindow;
    w->show();
    return a.exec();
}
