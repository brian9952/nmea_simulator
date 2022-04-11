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

    // widgets
    QPushButton *okButton;

    // functions
    QString getConfig();

private slots:
    void updateComboBox();

private:
    QVector<QString> serialPorts;

    void createLayout();
    void detectSerialPorts();
    void createConnection();

    QLabel *titleLabel;
    QLabel *warningLabel;
    QComboBox *serialPortsList;
    QPushButton *cancelButton;

    QTimer *serialCheckTimer;

};

#endif // STARTUPDIALOG_H
