#include "serialportdialog.h"
#include <QtWidgets>
#include <QSerialPort>

SerialPortDialog::SerialPortDialog(QWidget *parent) : QDialog(parent)
{

    QSerialPort *port = new QSerialPort;

}
