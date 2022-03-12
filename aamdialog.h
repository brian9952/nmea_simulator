#ifndef AAMDIALOG_H
#define AAMDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;

class AAMDialog : public QDialog
{

    Q_OBJECT

public:
    AAMDialog(QWidget *parent = nullptr);

private:
    void createLayout();

    QLabel *hello;
};

#endif // AAMDIALOG_H
