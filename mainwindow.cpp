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
    conf = new PortConfigs;

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

    // open startup dialog
    startupDialog->show();
    startupDialog->raise();
    startupDialog->activateWindow();

    // create threads
    serialThreads = new SerialThreads(sendSerialConsole, receiveSerialConsole, statusBar, this);
    serialThreads->setPortConfigs(conf);
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

    // console config
    QLabel *sendLabel = new QLabel(tr("Transfer's Console"));
    sendSerialConsole = new QPlainTextEdit;
    sendSerialConsole->setReadOnly(true);
    sendSerialConsole->setMaximumBlockCount(500);

    QLabel *receiveLabel =  new QLabel(tr("Receive's Console"));
    receiveSerialConsole = new QPlainTextEdit;
    receiveSerialConsole->setReadOnly(true);
    receiveSerialConsole->setMaximumBlockCount(500);

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
    //nmeaDataTitle->setFixedWidth(160);
    nmeaDataTitleLayout->addWidget(nmeaDataTitle);

    // insert layout into nmea data layout
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

    // startup dialog apply
    connect(startupDialog->okButton, SIGNAL(clicked()),
            this, SLOT(startupConfig()));

    // config apply signal
    connect(serialPortDialog->applyButton, SIGNAL(clicked()),
            this, SLOT(applyPortConfigs()));

    // aamdialog
    connect(aamDialog->addButton, SIGNAL(clicked()),
            addDataMapper, SLOT(map()));
    addDataMapper->setMapping(aamDialog->addButton, 0);

    // bodDialog
    connect(bodDialog->addButton, SIGNAL(clicked()),
            addDataMapper, SLOT(map()));
    addDataMapper->setMapping(bodDialog->addButton, 1);

    // dptDialog
    connect(dptDialog->addButton, SIGNAL(clicked()),
            addDataMapper, SLOT(map()));
    addDataMapper->setMapping(dptDialog->addButton, 2);

    // rotDialog
    connect(rotDialog->addButton, SIGNAL(clicked()),
            addDataMapper, SLOT(map()));
    addDataMapper->setMapping(rotDialog->addButton, 3);

    connect(addDataMapper, SIGNAL(mapped(int)),
            this, SLOT(addData(int)));


    // checkbox signal mapper
    checkboxMapper = new QSignalMapper;
    connect(checkboxMapper, SIGNAL(mapped(int)),
            this, SLOT(changeDataState(int)));

    // duration signal mapper
    durationMapper = new QSignalMapper;
    connect(durationMapper, SIGNAL(mapped(int)),
            this, SLOT(changeDataState(int)));

    // cancel button signal mapper
    cancelMapper = new QSignalMapper;
    connect(cancelMapper, SIGNAL(mapped(int)),
            this, SLOT(deleteRunningData(int)));


}

void MainWindow::createDialog(){
    startupDialog = new startupdialog();
    serialPortDialog = new SerialPortDialog();
    aamDialog = new AAMDialog();
    bodDialog = new BODDialog();
    dptDialog = new DPTDialog();
    rotDialog = new ROTDialog();
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

int MainWindow::searchDataId(int index){
    for(int i = 0; i < dataFrontend.length(); i++){
        if(dataFrontend[i]->id == index){
            return i;
        }
    }
    return -1;
}

// SLOTS
void MainWindow::openPortConfigDialog(){
    serialPortDialog->refreshPortList();
    serialPortDialog->show();
    serialPortDialog->raise();
    serialPortDialog->activateWindow();
}

void MainWindow::startupConfig(){
    conf->portName = startupDialog->getConfig();
    serialThreads->setPortConfigs(conf);
    startupDialog->close();
}

void MainWindow::applyPortConfigs(){
    int val;

    // port name
    conf->portName = serialPortDialog->portNameCombobox->currentText();

    // baud rate
    val = serialPortDialog->baudRateCombobox->currentData().toInt();
    QSerialPort::BaudRate baudRate = static_cast<QSerialPort::BaudRate>(val);
    conf->baudRate = baudRate;

    // data bits
    val = serialPortDialog->dataBitsCombobox->currentData().toInt();
    QSerialPort::DataBits dataBits = static_cast<QSerialPort::DataBits>(val);
    conf->dataBits = dataBits;

    // parity bits
    val = serialPortDialog->parityCombobox->currentData().toInt();
    QSerialPort::Parity parity = static_cast<QSerialPort::Parity>(val);
    conf->parity = parity;

    // stop bits
    val = serialPortDialog->stopBitsCombobox->currentData().toInt();
    QSerialPort::StopBits stopBits = static_cast<QSerialPort::StopBits>(val);
    conf->stopBits = stopBits;

    // flow control
    val = serialPortDialog->flowControlCombobox->currentData().toInt();
    QSerialPort::FlowControl flowControl = static_cast<QSerialPort::FlowControl>(val);
    conf->flowControl = flowControl;

    serialThreads->setPortConfigs(conf);
    serialPortDialog->close();
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
        case 2:
            dptDialog->show();
            dptDialog->raise();
            dptDialog->activateWindow();
            break;
        default:
            return;
    }
}

void MainWindow::changeDataState(int index){
    std::cout << data->dataStatus[index]->dataNames.toStdString() << "is changed!" << std::endl;
    if(data->dataStatus[index]->isEnabled == false){
        data->dataStatus[index]->isEnabled = true;
    }else{
        data->dataStatus[index]->isEnabled = false;
        data->dataStatus[index]->sec = 0;
    }
}

void MainWindow::deleteRunningData(int index){
    int i = searchDataId(index);
    dataFrontend[i]->id = -1;

    // delete label
    delete dataFrontend[i]->labelData;

    // delete checkbox
    delete dataFrontend[i]->checkboxData;

    // delete delete button
    delete dataFrontend[i]->cancelButton;

    dataFrontend.erase(dataFrontend.begin() + i);

    // send the data to threads
    serialThreads->setAddedData(dataFrontend, data);

    // edit data struct
    data->dataStatus[index]->isAdded = false;
    data->dataStatus[index]->isEnabled = false;

    // enable button
    dataObjects[index]->dataAddButton->setEnabled(1);
}

void MainWindow::addData(int index){
    RunningData *newObj = new RunningData;
    QLabel *newDataLabel = new QLabel(convertAbbvr(data->dataStatus[index]->dataNames));
    QCheckBox *newDataCheckbox = new QCheckBox();

    // cancel button
    QPushButton *newCancelButton = new QPushButton();
    QIcon icon;
    icon.addFile("images/cancel_icon.png");
    newCancelButton->setIcon(icon);
    newCancelButton->setIconSize(QSize(10, 10));
    newCancelButton->setFixedSize(QSize(16, 16));

    // insert layout
    newObj->id = index;
    newObj->labelData = newDataLabel;
    newObj->checkboxData = newDataCheckbox;
    newObj->cancelButton = newCancelButton;

    // change data state
    data->dataStatus[index]->isAdded = true;
    data->dataStatus[index]->sec = 0;
    connect(newObj->checkboxData, SIGNAL(stateChanged(int)), checkboxMapper, SLOT(map()));
    checkboxMapper->setMapping(newObj->checkboxData, index);

    // create cancel connection
    connect(newObj->cancelButton, SIGNAL(clicked(bool)), cancelMapper, SLOT(map()));
    cancelMapper->setMapping(newObj->cancelButton, index);

    dataFrontend.push_back(newObj);

    QHBoxLayout *newDataLayout = new QHBoxLayout;
    newDataLayout->addWidget(newObj->labelData);
    newDataLayout->addStretch();
    newDataLayout->addWidget(newObj->checkboxData);
    newDataLayout->addWidget(newObj->cancelButton);

    nmeaDataLayout->insertLayout(nmeaDataLayout->count()-1, newDataLayout);

    // disable button
    dataObjects[index]->dataAddButton->setDisabled(1);

    // get configs
    switch(index){
        case 0:
            aamDialog->applyConfigs(data);
            data->dataStatus[index]->duration = data->aam->duration;
            aamDialog->close();
            break;
        case 1:
            bodDialog->applyConfigs(data);
            data->dataStatus[index]->duration = data->bod->duration;
            bodDialog->close();
            break;
        case 2:
            dptDialog->applyConfigs(data);
            data->dataStatus[index]->duration = data->dpt->duration;
            dptDialog->close();
            break;
        case 3:
            rotDialog->applyConfigs(data);
            data->dataStatus[index]->duration = data->rot->duration;
            rotDialog->close();
            break;
        default:
            break;
    }

    serialThreads->setAddedData(dataFrontend, data);

}

MainWindow::~MainWindow()
{
    delete serialThreads;
    delete ui;
}
