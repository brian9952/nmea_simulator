#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include<QDialog>
#include<QSerialPort>

class QLabel;
class QLineEdit; 
class QComboBox;
class QGroupBox;
class QPushButton;

class SerialPortDialog : public QDialog
{

    Q_OBJECT

public:
    SerialPortDialog(QWidget *parent = nullptr);


private:

    struct PortConfigs {
        QString portName = "/dev/ttyUSB0";
        QSerialPort::BaudRate baudRate = QSerialPort::Baud9600;
        QSerialPort::DataBits dataBits = QSerialPort::Data8;
        QSerialPort::Parity parity = QSerialPort::NoParity;
        QSerialPort::StopBits stopBits = QSerialPort::OneStop;
        QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
    };
    
    PortConfigs *configs;
    
    void createLayout();
    void createConnection();
    void detectSerialPorts();
    
    QGroupBox *serialPortBox;
    
    QLabel *portNameLabel;
    QLabel *baudRateLabel;
    QLabel *dataBitsLabel;
    QLabel *parityLabel;
    QLabel *stopBitsLabel;
    QLabel *flowControlLabel;
    
    QComboBox *portNameCombobox;
    QComboBox *baudRateCombobox;
    QComboBox *dataBitsCombobox;
    QComboBox *parityCombobox;
    QComboBox *stopBitsCombobox;
    QComboBox *flowControlCombobox;
    
    QPushButton *applyButton;
    QPushButton *cancelButton;

    QVector<QString> serialPorts;

};

#endif // SERIALPORTDIALOG_H
