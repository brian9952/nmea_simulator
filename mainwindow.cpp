#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //data = new nmeaData;
    createLayout();
}

void MainWindow::createLayout(){
    window = new QWidget;
    toolbar = new QToolBar;

    // create toolbar
    toolbar->addAction("File");
    toolbar->addAction("Settings");
    toolbar->addAction("View");
    toolbar->addAction("About");
    toolbar->addAction("Help");

    // create terminal
    sendSerialConsole = new QPlainTextEdit("TEST1");
    receiveSerialConsole = new QPlainTextEdit("TEST2");
    QVBoxLayout *consoleInnerLayout = new QVBoxLayout;

    consoleInnerLayout->addWidget(sendSerialConsole);
    consoleInnerLayout->addWidget(receiveSerialConsole);

    // create nmeadata list (dummy)
    for(int i = 0; i < 3; i++){
        QString labelName = "Data" + QString::number(i);
        QLabel *label = new QLabel(labelName);
        QCheckBox *checkbox = new QCheckBox;
        label->setBuddy(checkbox);

        labelData.push_back(label);
        checkboxData.push_back(checkbox);
        //dataFrontend->labelData.append(*label);
        //dataFrontend->checkboxData.append(*checkbox);
    }

    // create layout
    QVBoxLayout *nmeaDataLayout = new QVBoxLayout;

    for (int i = 0; i < 3; i++){
        QLabel *label = dynamic_cast<QLabel*>(labelData[i]);
        QCheckBox *checkbox = dynamic_cast<QCheckBox*>(checkboxData[i]);

        QHBoxLayout *dataLayout = new QHBoxLayout;
        dataLayout->addWidget(label);
        dataLayout->addWidget(checkbox);

        nmeaDataLayout->addLayout(dataLayout);
    }
    nmeaDataLayout->addStretch();

    // create tab widgets
    QHBoxLayout *innerLayout = new QHBoxLayout;
    innerLayout->addLayout(consoleInnerLayout);
    innerLayout->addLayout(nmeaDataLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(toolbar);
    mainLayout->addLayout(innerLayout);

    window->setLayout(mainLayout);
    setCentralWidget(window);

}

MainWindow::~MainWindow()
{
    delete ui;
}
