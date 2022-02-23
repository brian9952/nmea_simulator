#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "nmeadata.cpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QToolBar;
class QPlainTextEdit;
class QTabWidget;
class QLabel;
class QCheckBox;
class QTabWidget;
class QStatusBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    // data structures
    //struct DataFrontend {
    //    QVector<QLabel> labelData;
    //    QVector<QCheckBox> checkboxData;
    //};
    //DataFrontend *dataFrontend = new DataFrontend;

    QVector<QWidget*> labelData;
    QVector<QWidget*> checkboxData;

    QWidget *window;
    QToolBar *toolbar;
    QTabWidget *tabWidget;
    QPlainTextEdit *sendSerialConsole;
    QPlainTextEdit *receiveSerialConsole;
    QStatusBar *statusBar;

    void createLayout();

    //nmeaData *data;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
