#ifndef BODDIALOG_H
#define BODDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>

class QLabel;
class QComboBox;
class QPushButton;

class BODDialog : public QDialog
{

    Q_OBJECT

public:
    BODDialog(QWidget *parent = nullptr);

private slots:
    void bdtSyncLowValue(int val);
    void bdtSyncHighValue(int val);
    void bdmSyncLowValue(int val);
    void bdmSyncHighValue(int val);

private:
    void createLayout();
    void createConnection();

    QLabel *bdtLabel;
    QLabel *bdmLabel;
    QLabel *bdtLowValue;
    QLabel *bdtHighValue;
    QLabel *bdmLowValue;
    QLabel *bdmHighValue;
    QLabel *durationLabel;
    RangeSlider *bdtRangeSlider;
    RangeSlider *bdmRangeSlider;
    QComboBox *durationCombobox;
    QPushButton *addButton;
    QPushButton *cancelButton;

};

#endif // BODDIALOG_H
