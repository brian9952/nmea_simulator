#ifndef AAMDIALOG_H
#define AAMDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>

class QLabel;
class QLineEdit;

class AAMDialog : public QDialog
{

    Q_OBJECT

public:
    AAMDialog(QWidget *parent = nullptr);

private slots:
    void syncHighValue(int val);
    void syncLowValue(int val);

private:
    void createLayout();
    void createConnection();

    QLabel *acrLabel;
    QLabel *lowLabelValue;
    QLabel *highLabelValue;
    RangeSlider *acrRangeSlider;

};

#endif // AAMDIALOG_H
