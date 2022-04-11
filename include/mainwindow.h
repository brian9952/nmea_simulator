#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <datastructs.h>
#include <QMainWindow>
#include <Dialogs/startupdialog.h>
#include <Dialogs/serialportdialog.h>
#include <nmeadata.h>
#include <Dialogs/aamdialog.h>
#include <Dialogs/boddialog.h>
#include <Dialogs/dptdialog.h>
#include <Dialogs/rotdialog.h>
#include <Dialogs/mwvdialog.h>
#include <Dialogs/rsadialog.h>
#include <Dialogs/hdtdialog.h>
#include <threads.h>

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
    void startupConfig();
    void applyPortConfigs();
    void openNMEADialog(int i);
    void addData(int i);
    void changeDataState(int index);
    void deleteRunningData(int index);

private:
    QVector<RunningData*> dataFrontend;
    PortConfigs *conf;

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
    QSignalMapper *cancelMapper;

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

    // DIALOGS
    startupdialog *startupDialog;
    SerialPortDialog *serialPortDialog;
    AAMDialog *aamDialog;
    BODDialog *bodDialog;
    DPTDialog *dptDialog;
    ROTDialog *rotDialog;
    MWVDialog *mwvDialog;
    RSADialog *rsaDialog;
    HDTDialog *hdtDialog;

    // generic functions
    QString convertAbbvr(const QString &str);
    int searchDataId(int index);

    // threads
    SerialThreads *serialThreads;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
