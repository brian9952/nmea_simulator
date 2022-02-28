#ifndef TERMDIALOGTRY_H
#define TERMDIALOGTRY_H

#include<QDialog>

class QPlainTextEdit;
class QSerialPort;

class TermDialogTry : public QDialog
{
    Q_OBJECT

public:
    TermDialogTry(QWidget *parent = nullptr);
    ~TermDialogTry();

private:
    QPlainTextEdit *console;
    QSerialPort *serialPort;

    void createLayout();

};

#endif // TERMDIALOGTRY_H
