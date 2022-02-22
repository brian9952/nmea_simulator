#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include<QDialog>

class QLabel;
class QPushButton;
class QComboBox;

class StartupDialog : public QDialog {

    Q_OBJECT

public:
    StartupDialog(QWidget *parent = nullptr);
    ~StartupDialog();

private:

    void createLayout();

};

#endif // STARTUPDIALOG_H
