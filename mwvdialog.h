#ifndef MWVDIALOG_H
#define MWVDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>
#include "nmeadata.h"

class QPushButton;
class QLabel;
class QComboBox;

class MWVDialog : public QDialog
{

    Q_OBJECT

public:
    MWVDialog(QWidget *parent = nullptr);
    void applyConfigs(nmeaData *data);

    QPushButton *addButton;

private slots:
    void syncWaLowVal(int);
    void syncWaHighVal(int);
    void syncWsLowVal(int);
    void syncWsHighVal(int);

private:
    void createLayout();
    void createConnection();

    QLabel *waLowVal;
    QLabel *waHighVal;
    QLabel *wsLowVal;
    QLabel *wsHighVal;

    RangeSlider *waSlider;
    RangeSlider *wsSlider;

    QComboBox *durationCombobox;

    QPushButton *cancelButton;

};

#endif // MWVDIALOG_H
