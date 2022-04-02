#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QSerialPort>
#include <QtWidgets>

struct PortConfigs {
    QString portName = "none";
    QSerialPort::BaudRate baudRate = QSerialPort::Baud9600;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
};

struct RunningData {
    int id;
    QLabel *labelData;
    QCheckBox *checkboxData;
    QPushButton *cancelButton;
};

#endif // DATASTRUCTS_H
