#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtWidgets>
#include<QSerialPort>
#include<iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // create central widget
    mainWindow = new QWidget;

    createAction();
    createMenuBar();
    createCentralWindow();
    createStatusBar();
    createLayout();

    createDialog();

    data = new nmeaData;
    createNMEAWidgets();

    createConnection();
    //createTimers();

    // create threads
    sendThread = new SendDataThreads(sendSerialConsole, data, this);
}

void MainWindow::createMenuBar(){
    menuBar = new QMenuBar;

    // add file menu
    fileMenu = new QMenu;
    fileMenu = menuBar->addMenu("File");
    
    // add settings menu
    settingsMenu = new QMenu;
    settingsMenu = menuBar->addMenu("Settings");
    settingsMenu->addAction(openPortDialog);

    // add view menu
    viewMenu = new QMenu;
    viewMenu = menuBar->addMenu("View");

    // add about menu
    aboutMenu = new QMenu;
    aboutMenu = menuBar->addMenu("About");

    // add help menu
    helpMenu = new QMenu;
    helpMenu = menuBar->addMenu("Help");
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

    // add layout
    nmeaDataLayout = new QVBoxLayout;
    nmeaDataLayout->addStretch();

    // add title
    QHBoxLayout *nmeaDataTitleLayout = new QHBoxLayout;
    QLabel *nmeaDataTitle = new QLabel(tr("NMEA Data:"));
    nmeaDataTitle->setFixedWidth(160);
    nmeaDataTitleLayout->addWidget(nmeaDataTitle);

    // insert layout into nmea data layout
    nmeaDataLayout->setGeometry(QRect(0, 0, 80, 0));
    nmeaDataLayout->insertLayout(nmeaDataLayout->count() - 1, nmeaDataTitleLayout);

    // add tab widget
    tabWidget = new QTabWidget;
    tabWidget->addTab(consoleWidget, "Console");

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(nmeaDataTitleLayout);
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
        QLabel *label = new QLabel(data->dataStatus[i]->dataNames);
        QPushButton *button = new QPushButton(tr("Add"));

        innerLayout->addWidget(label);
        innerLayout->addStretch();
        innerLayout->addWidget(button);
        //innerLayout->addSpacing(15);

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
    connect(openPortDialog, SIGNAL(triggered()), this, SLOT(openPortConfigDialog()));
}

void MainWindow::createConnection(){
    dataDialogMapper = new QSignalMapper;

    // nmea data add button
    for(int i = 0; i < dataObjects.length(); i++){
        connect(dataObjects[i]->dataAddButton, SIGNAL(clicked()),
                dataDialogMapper, SLOT(map()));
        dataDialogMapper->setMapping(dataObjects[i]->dataAddButton, i);
    }

    // signal mapping
    connect(dataDialogMapper, SIGNAL(mapped(int)),
            this, SLOT(openNMEADialog(int)));

    // data add
    addDataMapper = new QSignalMapper;

    // aamdialog
    connect(aamDialog->addButton, SIGNAL(clicked()),
            addDataMapper, SLOT(map()));
    addDataMapper->setMapping(aamDialog->addButton, 0);

    // bodDialog
    connect(bodDialog->addButton, SIGNAL(clicked()),
            addDataMapper, SLOT(map()));
    addDataMapper->setMapping(bodDialog->addButton, 1);

    connect(addDataMapper, SIGNAL(mapped(int)),
            this, SLOT(addData(int)));

    // checkbox signal mapper
    checkboxMapper = new QSignalMapper;
    connect(checkboxMapper, SIGNAL(mapped(int)), this, SLOT(changeDataState(int)));

    // duration signal mapper
    durationMapper = new QSignalMapper;
    connect(durationMapper, SIGNAL(mapped(int)), this, SLOT(changeDataState(int)));

}

void MainWindow::createDialog(){
    aamDialog = new AAMDialog();
    bodDialog = new BODDialog;
}

// Generic Functions
QString MainWindow::convertAbbvr(const QString &str){
    str.toStdString();
    QString new_str;
    for(int i = 0; i < str.length(); i++){
        if(i == 0)
            new_str.push_back(str[i]);
        if(str[i] == ' ')
            new_str.push_back(str[i+1]);
    }
    return new_str;
}

// SLOTS
void MainWindow::openPortConfigDialog(){
    serialPortDialog = new SerialPortDialog();
    serialPortDialog->setAttribute(Qt::WA_DeleteOnClose);
    serialPortDialog->show();
    serialPortDialog->raise();
    serialPortDialog->activateWindow();
}

void MainWindow::openNMEADialog(int i){
    switch(i){
        case 0:
            aamDialog->show();
            aamDialog->raise();
            aamDialog->activateWindow();
            break;
        case 1:
            bodDialog->show();
            bodDialog->raise();
            bodDialog->activateWindow();
            break;
        default:
            return;
    }
}

void MainWindow::changeDataState(int index){
    if(data->dataStatus[index]->isEnabled == false){
        data->dataStatus[index]->isEnabled = true;
    }else{
        data->dataStatus[index]->isEnabled = false;
        data->dataStatus[index]->sec = 0;
    }
}

void MainWindow::addData(int index){
    RunningData *newObj = new RunningData;
    QLabel *newDataLabel = new QLabel(convertAbbvr(data->dataStatus[index]->dataNames));
    QCheckBox *newDataCheckbox = new QCheckBox();

    // insert layout
    newObj->id = index;
    newObj->labelData = newDataLabel;
    newObj->checkboxData = newDataCheckbox;

    // change data state
    data->dataStatus[index]->isAdded = true;
    data->dataStatus[index]->sec = 0;
    connect(newObj->checkboxData, SIGNAL(stateChanged(int)), checkboxMapper, SLOT(map()));
    checkboxMapper->setMapping(newObj->checkboxData, index);

    dataFrontend.push_back(newObj);

    QHBoxLayout *newDataLayout = new QHBoxLayout;
    newDataLayout->addWidget(newObj->labelData);
    newDataLayout->addWidget(newObj->checkboxData);

    nmeaDataLayout->insertLayout(nmeaDataLayout->count()-1, newDataLayout);

    // get configs
    switch(index){
        case 0:
            aamDialog->applyConfigs(data);
            sendThread->setAddedData(dataFrontend);
            data->dataStatus[index]->duration = data->aam->duration;
            aamDialog->close();
            break;
        case 1:
            bodDialog->applyConfigs(data);
            sendThread->setAddedData(dataFrontend);
            data->dataStatus[index]->duration = data->bod->duration;
            bodDialog->close();
            break;
        default:
            break;
    }
}

MainWindow::~MainWindow()
{
    delete sendThread;
    delete ui;
}
