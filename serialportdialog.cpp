#include "serialportdialog.h"
#include <QtWidgets>
#include <QSerialPort>

SerialPortDialog::SerialPortDialog(QWidget *parent) : QDialog(parent)
{

    PortConfigs *configs = new PortConfigs;
    configs->baudRate = QSerialPort::Baud115200;
    QSerialPort *port = new QSerialPort;
    port->setBaudRate(configs->baudRate);

}
