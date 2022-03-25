#ifndef DPTDIALOG_H
#define DPTDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>
#include "nmeadata.h"

class QPushButton;
class QLabel;
class QComboBox;

class DPTDialog : public QDialog
{

    Q_OBJECT

public:
    DPTDialog(QWidget *parent = nullptr);

    QPushButton *addButton;

    void applyConfigs(nmeaData *data);

private:
    // functions
    void createLayout();
    void createConnection();

    // classes
    QLabel *wdLabel;
    QLabel *maxRangeLabel;
    QLabel *durationLabel;

    RangeSlider *wdSlider;
    RangeSlider *maxRangeSlider;

    QLabel *wdLowVal;
    QLabel *wdHighVal;
    QLabel *maxRangeLowVal;
    QLabel *maxRangeHighVal;

    QComboBox *durationCombobox;

    QPushButton *cancelButton;
};

#endif // DPTDIALOG_H
