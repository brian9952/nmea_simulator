#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialportdialog.h"
#include "nmeadata.h"
#include "aamdialog.h"
#include "boddialog.h"
#include "threads.h"

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
class QSignalMapper;
class QVBoxLayout;

class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void openPortConfigDialog();
    void openNMEADialog(int i);
    void addData(int i);
    void changeDataState(int index);

private:
    QVector<RunningData*> dataFrontend;

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

    // layouts
    QVBoxLayout *nmeaDataLayout;

    // widgets
    QTabWidget *tabWidget;
    QPlainTextEdit *sendSerialConsole;
    QPlainTextEdit *receiveSerialConsole;
    QStatusBar *statusBar;
    QSerialPort *serialPort;

    // signal mapper
    QSignalMapper *dataDialogMapper;
    QSignalMapper *addDataMapper;
    QSignalMapper *checkboxMapper;
    QSignalMapper *durationMapper;

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

    // creation functions
    void createMenuBar();
    void createCentralWindow();
    void createStatusBar();
    void createLayout();
    void createNMEAWidgets();
    void createAction();
    void createConnection();
    void createDialog();
    //void createTimers();

    // Data Execution Functions
    //QTimer *sendTimer;
    //void sendData();

    // DIALOGS
    SerialPortDialog *serialPortDialog;
    AAMDialog *aamDialog;
    BODDialog *bodDialog;

    // generic functions
    QString convertAbbvr(const QString &str);

    // threads
    SendDataThreads *sendThread;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
