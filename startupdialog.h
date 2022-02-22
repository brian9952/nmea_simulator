#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include<QDialog>

class QLabel;
class QPushButton;
class QComboBox;

class startupdialog : public QDialog
{
    Q_OBJECT

public:
    startupdialog(QWidget *parent = nullptr);
    ~startupdialog();

private:
    QVector<QString> serialPorts;

    void createLayout();
    void detectSerialPorts();

    QLabel *titleLabel;
    QLabel *warningLabel;
    QComboBox *serialPortsList;
    QPushButton *okButton;
    QPushButton *cancelButton;

};

#endif // STARTUPDIALOG_H
