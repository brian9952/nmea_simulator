#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtWidgets>
#include<QSerialPort>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // create central widget
    mainWindow = new QWidget;

    createMenuBar();
    createCentralWindow();
    createStatusBar();
    createLayout();

    data = new nmeaData;
    createNMEAWidgets();

    createSerialPort();

}

void MainWindow::createMenuBar(){
    menuBar = new QMenuBar;

    // add file menu
    QMenu *fileMenu = menuBar->addMenu("File");
    
    // add settings menu
    QMenu *settingsMenu = menuBar->addMenu("Settings");
    settingsMenu->addAction(openPortDialog);

    // add view menu
    QMenu *viewMenu = menuBar->addMenu("View");

    // add about menu
    QMenu *aboutMenu = menuBar->addMenu("About");

    // add help menu
    QMenu *helpMenu = menuBar->addMenu("Help");
    fileMenu->addAction("Test");
    menuBar->addAction("Settings");
    menuBar->addAction("View");
    menuBar->addAction("About");
    menuBar->addAction("Help");
}

void MainWindow::createCentralWindow(){
    mainWidget = new QWidget;

    // create terminal
    QWidget *consoleWidget = new QWidget;
    QLabel *sendLabel = new QLabel(tr("Transfer's Console"));
    sendSerialConsole = new QPlainTextEdit;
    QLabel *receiveLabel =  new QLabel(tr("Receive's Console"));
    receiveSerialConsole = new QPlainTextEdit;

    QVBoxLayout *innerConsoleLayout = new QVBoxLayout;
    innerConsoleLayout->addWidget(sendLabel);
    innerConsoleLayout->addWidget(sendSerialConsole);
    innerConsoleLayout->addWidget(receiveLabel);
    innerConsoleLayout->addWidget(receiveSerialConsole);

    consoleWidget->setLayout(innerConsoleLayout);

    // create nmeadata list (dummy)
    for(int i = 0; i < 3; i++){
        QString labelName = "Data" + QString::number(i);
        QLabel *label = new QLabel(labelName);
        QCheckBox *checkbox = new QCheckBox;
        label->setBuddy(checkbox);

        DataFrontend *obj = new DataFrontend;
        obj->labelData = label;
        obj->checkboxData = checkbox;

        dataFrontend.push_back(obj);
    }

    QVBoxLayout *nmeaDataLayout = new QVBoxLayout;

    QLabel *nmeaDataLabel = new QLabel(tr("NMEA Data:"));
    nmeaDataLayout->addWidget(nmeaDataLabel);

    for (int i = 0; i < 3; i++){
        QHBoxLayout *dataLayout = new QHBoxLayout;
        dataLayout->addWidget(dataFrontend[i]->labelData);
        dataLayout->addWidget(dataFrontend[i]->checkboxData);

        nmeaDataLayout->addLayout(dataLayout);
    }
    nmeaDataLayout->addStretch();

    // add tab widget
    tabWidget = new QTabWidget;
    tabWidget->addTab(consoleWidget, "Console");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(nmeaDataLayout);

    mainWidget->setLayout(mainLayout);
}

void MainWindow::createStatusBar(){
    statusBar = new QStatusBar;

    statusBar->showMessage("Ready");
}

void MainWindow::createLayout(){
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(statusBar);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainWindow->setLayout(mainLayout);
    setCentralWidget(mainWindow);
}

void MainWindow::createNMEAWidgets(){
    dataList = new QWidget;

    QVBoxLayout *dataListLayout = new QVBoxLayout;
    for(int i = 0; i < data->dataNumbers; i++){
        QHBoxLayout *innerLayout = new QHBoxLayout;
        QLabel *label = new QLabel(data->dataNames[i]);
        QPushButton *button = new QPushButton(tr("Add"));

        innerLayout->addWidget(label);
        innerLayout->addWidget(button);
        innerLayout->addSpacing(15);

        // vector processing
        NMEADataList *dataList = new NMEADataList;
        dataList->dataId = i;
        dataList->dataName = label;
        dataList->dataAddButton = button;
        dataObjects.push_back(dataList);

        dataListLayout->addLayout(innerLayout);
    }
    dataListLayout->addStretch();

    dataList->setLayout(dataListLayout);
    tabWidget->addTab(dataList, "Data List");

}

void MainWindow::createAction(){
    // open port settings action
    openPortDialog = new QAction(tr("Port Config"), this);
    openPortDialog->setStatusTip(tr("open port settings dialog"));
    connect(openPortDialog, &QAction::trigerred, this, openPortConfigDialog());
}

void MainWindow::createSerialPort(){

    serialPort = new QSerialPort;

}

// SLOTS
void MainWindow::openPortConfigDialog(){
    SerialPortDialog *serialPortDialog = new SerialPortDialog;
    serialPortDialog->setModal();
    serialPortDialog->setAttribute(Qt::WA_DeleteOnClose);
    serialPortDialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
