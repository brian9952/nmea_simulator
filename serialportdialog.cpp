#include "serialportdialog.h"

#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>

SerialPortDialog::SerialPortDialog(QWidget *parent) : QDialog(parent)
{

    configs = new PortConfigs;

    // create dialog layout
    createLayout();
    
    configs->baudRate = QSerialPort::Baud115200;
    QSerialPort *port = new QSerialPort;
    port->setBaudRate(configs->baudRate);

}

void SerialPortDialog::detectSerialPorts(){

    QSerialPortInfo *serialInfo = new QSerialPortInfo;
    QList<QSerialPortInfo> sports;
    
    sports = serialInfo->availablePorts();
    
    for(int i = 0; i < sports.length(); i++){
        serialPorts.append(sports[i].portName());
    }
    
    delete serialInfo;
    
}

void SerialPortDialog::createLayout(){

    detectSerialPorts();
    
    // create port name label and combobox
    portNameLabel = new QLabel(tr("Port Name: "));
    portNameCombobox = new QComboBox();
    for(int i = 0; i < serialPorts.length(); i++){
        portNameCombobox->addItem(serialPorts[i]);
    }
    
    // create layout
    QHBoxLayout *portNameLayout = new QHBoxLayout;
    portNameLayout->addWidget(portNameLabel);
    portNameLayout->addWidget(portNameCombobox);
    
    // create baud rate configs
    baudRateLabel = new QLabel(tr("Baud Rate: "));
    baudRateCombobox = new QComboBox();
    baudRateCombobox->addItem("1200");
    baudRateCombobox->addItem("2400");
    baudRateCombobox->addItem("4800");
    baudRateCombobox->addItem("9600");
    baudRateCombobox->addItem("19200");
    baudRateCombobox->addItem("38400");
    baudRateCombobox->addItem("57600");
    baudRateCombobox->addItem("115200");
    
    // create layout
    QHBoxLayout *baudRateLayout = new QHBoxLayout;
    baudRateLayout->addWidget(baudRateLabel);
    baudRateLayout->addWidget(baudRateCombobox);
    
    // create data bits configs
    dataBitsLabel = new QLabel(tr("Data Bits: "));
    dataBitsCombobox = new QComboBox();
    dataBitsCombobox->addItem("5");
    dataBitsCombobox->addItem("6");
    dataBitsCombobox->addItem("7");
    dataBitsCombobox->addItem("8");
    
    // create layout
    QHBoxLayout *dataBitsLayout = new QHBoxLayout;
    dataBitsLayout->addWidget(dataBitsLabel);
    dataBitsLayout->addWidget(dataBitsCombobox);
    
    // create parity configs
    parityLabel = new QLabel(tr("Parity: "));
    parityCombobox = new QComboBox();
    parityCombobox->addItem("No Parity");
    parityCombobox->addItem("Even Parity");
    parityCombobox->addItem("Odd Parity");
    parityCombobox->addItem("Mark Parity");
    
    // create layout
    QHBoxLayout *parityLayout = new QHBoxLayout;
    parityLayout->addWidget(parityLabel);
    parityLayout->addWidget(parityCombobox);
    
    // create stop bits configs
    stopBitsLabel = new QLabel(tr("Stop Bits: "));
    stopBitsCombobox = new QComboBox();
    stopBitsCombobox->addItem("One Stop");
    stopBitsCombobox->addItem("One and Half Stop");
    stopBitsCombobox->addItem("Two Stop");
    
    // create layout
    QHBoxLayout *stopBitsLayout = new QHBoxLayout;
    stopBitsLayout->addWidget(stopBitsLabel);
    stopBitsLayout->addWidget(stopBitsCombobox);
    
    // create flow control configs
    flowControlLabel = new QLabel(tr("Flow Control"));
    flowControlCombobox = new QComboBox();
    flowControlCombobox->addItem("No Flow Control");
    flowControlCombobox->addItem("Hardware Control");
    flowControlCombobox->addItem("Software Control");

    // create layout
    QHBoxLayout *flowControlLayout = new QHBoxLayout;
    flowControlLayout->addWidget(flowControlLabel);
    flowControlLayout->addWidget(flowControlCombobox);
    
    // create left three labels and dropdown box
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(portNameLayout);
    leftLayout->addLayout(baudRateLayout);
    leftLayout->addLayout(dataBitsLayout);
    
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(parityLayout);
    rightLayout->addLayout(stopBitsLayout);
    rightLayout->addLayout(flowControlLayout);
    
    QHBoxLayout *configsLayout = new QHBoxLayout;
    configsLayout->addLayout(leftLayout);
    configsLayout->addLayout(rightLayout);
    
    // create buttons
    applyButton = new QPushButton(tr("Apply"));
    cancelButton = new QPushButton(tr("Cancel"));
    
    // create layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(applyButton);
    buttonLayout->addWidget(cancelButton);
    
    // create main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(configsLayout);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);

}

/*
void SerialPortDialog::updateConfig(){
    // set port name
    configs->portName = portNameCombobox->itemData(portNameCombobox->currentIndex());

    // set baud rate
    QString baudRateString = baudRateCombobox->itemData(baudRateCombobox->currentIndex());

    switch(baudRateString){
        case "1200":
            configs->baudRate = QSerialPort::Baud1200;
        case "2400":
            configs->baudRate = QSerialPort::Baud2400;
        case "4800":
            configs->baudRate = QSerialPort::Baud4800;
        case "9600":
            configs->baudRate = 
    }

}
*/

void SerialPortDialog::createConnection(){
    // apply button connection
    connect(applyButton, SIGNAL(clicked()), this, SLOT(updateConfig()));

    // cancel button connection
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
