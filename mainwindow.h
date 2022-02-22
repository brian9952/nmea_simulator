#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QToolBar;
class QPlainTextEdit;
class QTabWidget;
class QLabel;
class QCheckBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *window;
    QToolBar *toolbar;

    void createLayout();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
