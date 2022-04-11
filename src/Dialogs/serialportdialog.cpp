#include <Dialogs/serialportdialog.h>

#include <QtWidgets>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>

SerialPortDialog::SerialPortDialog(QWidget *parent) : QDialog(parent)
{
    // create dialog layout
    createLayout();
    createConnection();
}

void SerialPortDialog::detectSerialPorts(){
    serialPorts.clear();

    QSerialPortInfo *serialInfo = new QSerialPortInfo;
    QList<QSerialPortInfo> sports;

    sports = serialInfo->availablePorts();
    
    for(int i = 0; i < sports.length(); i++){
        serialPorts.append(sports[i].portName());
    }
    
    delete serialInfo;
    
}

void SerialPortDialog::createLayout(){

    //detectSerialPorts();
    
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

    // generate baud rate values
    for(int i = 1200; i <= 115200; i*=2){
        baudRateCombobox->addItem(QString::number(i), QVariant(i));
        if(i == 38400)
            i += 19200;
    }
    
    // create layout
    QHBoxLayout *baudRateLayout = new QHBoxLayout;
    baudRateLayout->addWidget(baudRateLabel);
    baudRateLayout->addWidget(baudRateCombobox);
    
    // create data bits configs
    dataBitsLabel = new QLabel(tr("Data Bits: "));
    dataBitsCombobox = new QComboBox();
    for(int i = 5; i < 9; i++){
        dataBitsCombobox->addItem(QString::number(i), QVariant(i));
    }
    
    // create layout
    QHBoxLayout *dataBitsLayout = new QHBoxLayout;
    dataBitsLayout->addWidget(dataBitsLabel);
    dataBitsLayout->addWidget(dataBitsCombobox);
    
    // create parity configs
    parityLabel = new QLabel(tr("Parity: "));
    parityCombobox = new QComboBox();
    parityCombobox->addItem("No Parity", QVariant(0));
    parityCombobox->addItem("Even Parity", QVariant(1));
    parityCombobox->addItem("Odd Parity", QVariant(2));
    parityCombobox->addItem("Mark Parity", QVariant(3));
    
    // create layout
    QHBoxLayout *parityLayout = new QHBoxLayout;
    parityLayout->addWidget(parityLabel);
    parityLayout->addWidget(parityCombobox);
    
    // create stop bits configs
    stopBitsLabel = new QLabel(tr("Stop Bits: "));
    stopBitsCombobox = new QComboBox();
    stopBitsCombobox->addItem("One Stop", QVariant(0));
    stopBitsCombobox->addItem("One and Half Stop", QVariant(1));
    stopBitsCombobox->addItem("Two Stop", QVariant(2));
    
    // create layout
    QHBoxLayout *stopBitsLayout = new QHBoxLayout;
    stopBitsLayout->addWidget(stopBitsLabel);
    stopBitsLayout->addWidget(stopBitsCombobox);
    
    // create flow control configs
    flowControlLabel = new QLabel(tr("Flow Control"));
    flowControlCombobox = new QComboBox();
    flowControlCombobox->addItem("No Flow Control", QVariant(0));
    flowControlCombobox->addItem("Hardware Control", QVariant(1));
    flowControlCombobox->addItem("Software Control", QVariant(2));

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

    QSerialPort::BaudRate val = static_cast<QSerialPort::BaudRate>(1200);
    std::cout << val << std::endl;
    
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

void SerialPortDialog::refreshPortList(){
    detectSerialPorts();
    portNameCombobox->clear();
    for(int i = 0; i < serialPorts.length(); i++){
        portNameCombobox->addItem(serialPorts[i]);
    }
}

void SerialPortDialog::createConnection(){
    // cancel button connection
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
