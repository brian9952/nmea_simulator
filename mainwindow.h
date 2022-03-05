#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialportdialog.h"
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

class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPortConfigDialog();

private:

    // data structures
    struct DataFrontend {
        QLabel *labelData;
        QCheckBox *checkboxData;
    };
    QVector<DataFrontend*> dataFrontend;

    struct SerialPortConfigs {
        QString portName;
        QString baudRate;
        QString dataBits;
        QString parity;
        QString stopBits;
        QString flowControl;
    };

    // main widgets & layouts
    QWidget *mainWidget;
    QWidget *mainWindow;
    QWidget *dataList;

    // objects
    // menu
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *settingsMenu;
    QMenu *viewMenu;
    QMenu *aboutMenu;
    QMenu *helpMenu;

    // widgets
    QTabWidget *tabWidget;
    QPlainTextEdit *sendSerialConsole;
    QPlainTextEdit *receiveSerialConsole;
    QStatusBar *statusBar;
    QSerialPort *serialPort;

    // data Objects
    struct NMEADataList {
        int dataId;
        QLabel *dataName;
        QPushButton *dataAddButton;
    };
    QVector<NMEADataList*> dataObjects;

    nmeaData *data;

    // ACTIONS
    // setting actions
    QAction *openPortDialog;

    void createMenuBar();
    void createCentralWindow();
    void createStatusBar();
    void createLayout();
    void createNMEAWidgets();
    void createAction();

    void createSerialPort();

    //nmeaData *data;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
