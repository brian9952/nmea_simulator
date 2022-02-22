#include<QDebug>
#include<QSerialPortInfo>
#include<QTextStream>
#include<QtWidgets>
#include "startupdialog.h"

startupdialog::startupdialog(QWidget *parent) : QDialog(parent)
{
    detectSerialPorts();
    createLayout();
}

void startupdialog::detectSerialPorts(){
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
    warningLabel = new QLabel(tr("Serial ports not found!"));
    serialPortsList = new QComboBox;

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *confLayout = new QHBoxLayout;
    confLayout->addWidget(okButton);
    confLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);

    if(serialPorts.length() == 0){
        mainLayout->addWidget(warningLabel);
    }else{
        for(int i = 0; i < serialPorts.length(); i++){
            serialPortsList->addItem(serialPorts[i]);
        }
    }

    mainLayout->addWidget(serialPortsList);
    mainLayout->addLayout(confLayout);

    setLayout(mainLayout);

}

startupdialog::~startupdialog(){

}
