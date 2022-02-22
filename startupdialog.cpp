#include<QDebug>
#include<QSerialPortInfo>
#include<QTextStream>
#include<QtWidgets>
#include "startupdialog.h"

startupdialog::startupdialog(QWidget *parent) : QDialog(parent)
{
    detectSerialPorts();
    createLayout();
    createConnection();
}

void startupdialog::detectSerialPorts(){
    serialPorts.clear();
    QSerialPortInfo *serialInfo = new QSerialPortInfo;
    QList<QSerialPortInfo> sports;

    sports = serialInfo->availablePorts();

    for(int i = 0; i < sports.length(); i++){
        serialPorts.append(sports[i].portName());
    }

    delete serialInfo;
}

void startupdialog::createLayout(){

    titleLabel = new QLabel(tr("Choose serial ports"));
    warningLabel = new QLabel(tr("Warning: serial ports not found!"));
    serialPortsList = new QComboBox;

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *confLayout = new QHBoxLayout;
    confLayout->addSpacing(50);
    confLayout->addWidget(okButton);
    confLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);

    if(serialPorts.length() == 0){
        mainLayout->addWidget(warningLabel);
    }else{
        for(int i = 0; i < serialPorts.length(); i++){
            serialPortsList->addItem(serialPorts[i]);
        }
    }

    mainLayout->addWidget(serialPortsList);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(confLayout);

    setLayout(mainLayout);

}

void startupdialog::createConnection(){
    // check if port is open
    serialCheckTimer = new QTimer(this);
    connect(serialCheckTimer, SIGNAL(timeout()),
            this, SLOT(updateComboBox()));
    serialCheckTimer->start(10000);
}

void startupdialog::updateComboBox(){
    detectSerialPorts();
    serialPortsList->clear();
    if(serialPorts.length() == 0){
        warningLabel->setVisible(true);
    }else{
        for(int i = 0;i < serialPorts.length(); i++){
            serialPortsList->addItem(serialPorts[i]);
        }
        warningLabel->setVisible(false);
    }
}

startupdialog::~startupdialog(){

}
