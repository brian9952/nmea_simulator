#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include "datastructs.h"
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

    QPushButton *applyButton;

    // combobox
    QComboBox *portNameCombobox;
    QComboBox *baudRateCombobox;
    QComboBox *dataBitsCombobox;
    QComboBox *parityCombobox;
    QComboBox *stopBitsCombobox;
    QComboBox *flowControlCombobox;

private:

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
    
    QPushButton *cancelButton;

    QVector<QString> serialPorts;

};

#endif // SERIALPORTDIALOG_H
