#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtWidgets>

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
}

void MainWindow::createMenuBar(){
    menuBar = new QMenuBar;

    // add menus
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("Test");
    menuBar->addAction("Settings");
    menuBar->addAction("View");
    menuBar->addAction("About");
    menuBar->addAction("Help");

    // add frame
    //QFrame *topFillerFrame = new QFrame;
    //topFillerFrame->setFrameStyle(QFrame::HLine | QFrame::Plain);
    //topFillerFrame->setParent(topFiller);
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
    mainLayout->addLayout(nmeaDataLayout);

    mainWidget->setLayout(mainLayout);

    //QFrame *testFrame = new QFrame;
    //testFrame->setFrameStyle(QFrame::HLine | QFrame::Plain);
    //testFrame->setParent(mainWidget);
}

void MainWindow::createStatusBar(){
    statusBar = new QStatusBar;

    statusBar->showMessage("Ready");

    //QFrame *bottomFillerFrame = new QFrame;
    //bottomFillerFrame->setFrameStyle(QFrame::HLine | QFrame::Plain);
    //bottomFillerFrame->setParent(bottomFiller);
}

void MainWindow::createLayout(){

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(menuBar);
    mainLayout->addWidget(mainWidget);
    mainLayout->addWidget(statusBar);

    mainWindow->setLayout(mainLayout);
    setCentralWidget(mainWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}
