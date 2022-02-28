#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include<QDialog>
#include<QSerialPort>

class QLabel;
class QPushButton;

class SerialPortDialog : public QDialog
{
public:
    Q_OBJECT

    SerialPortDialog(QWidget *parent = nullptr);

private:

    struct PortConfigs {
        QString portName;
        QSerialPort::BaudRate baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };

};

#endif // SERIALPORTDIALOG_H
