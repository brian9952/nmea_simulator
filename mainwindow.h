#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nmeadata.h"

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
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    // data structures
    struct DataFrontend {
        QLabel *labelData;
        QCheckBox *checkboxData;
    };
    QVector<DataFrontend*> dataFrontend;

    // main widgets & layouts
    QWidget *mainWidget;
    QWidget *mainWindow;
    QWidget *dataList;

    // objects
    QMenuBar *menuBar;
    QTabWidget *tabWidget;
    QPlainTextEdit *sendSerialConsole;
    QPlainTextEdit *receiveSerialConsole;
    QStatusBar *statusBar;

    // data Objects
    struct NMEADataList {
        int dataId;
        QLabel *dataName;
        QPushButton *dataAddButton;
    };
    QVector<NMEADataList*> dataObjects;

    nmeaData *data;

    void createMenuBar();
    void createCentralWindow();
    void createStatusBar();
    void createLayout();
    void createNMEAWidgets();

    void showNMEADialog();

    //nmeaData *data;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
