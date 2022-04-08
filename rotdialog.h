#ifndef ROTDIALOG_H
#define ROTDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>
#include "nmeadata.h"

class QPushButton;
class QLabel;
class QComboBox;

class ROTDialog : public QDialog
{

    Q_OBJECT

public:
    ROTDialog(QWidget *parent = nullptr);
    void applyConfigs(nmeaData *data);

    QPushButton *addButton;

private slots:
    void rotSyncLowValue(int);
    void rotSyncHighValue(int);

private:
    void createLayout();
    void createConnection();
    float convRotValue(int val);

    QLabel *rotLabel;
    QLabel *durationLabel;
    QLabel *rotLowVal;
    QLabel *rotHighVal;

    RangeSlider *rotSlider;
    QComboBox *durationCombobox;

    QPushButton *cancelButton;

};

#endif // ROTDIALOG_H
