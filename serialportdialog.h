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

    enum BaudRate {
        Baud1200 = 1200,
        Baud2400 = 2400,
        Baud4800 = 4800,
        Baud9600 = 9600,
        Baud19200 = 19200,
        Baud38400 = 38400,
        Baud57600 = 57600,
        Baud76800 = 76800,
        Baud115200 = 115200,
        Baud230400 = 230400,
        Baud460800 = 460800,
        Baud576000 = 576000
    };

    enum DataBits {
        Data5,
        Data6,
        Data7,
        Data8,
        UnknownDataBits
    };

    enum Parity {
        NoParity,
        EvenParity,
        OddParity,
        SpaceParity,
        MarkParity,
        UnknownParity
    };

    enum StopBits {
        OneStop,
        OneAndHalfStop,
        TwoStop,
        UnknownStopBits
    };

    enum FlowControl {
        NoFlowControl,
        HardwareControl,
        SoftwareControl,
        UnknownFlowControl
    };

    struct PortConfigs {
        QString portName;
        int baudRate;
        DataBits dataBits;
        Parity parity;
        StopBits stopBits;
        FlowControl flowControl;
    };

};

#endif // SERIALPORTDIALOG_H
