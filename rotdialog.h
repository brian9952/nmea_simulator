#ifndef ROTDIALOG_H
#define ROTDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>
#include "nmeadata.h"

class QPushButton;
class QLabel;

class ROTDialog : public QDialog
{

    Q_OBJECT

public:
    ROTDialog(QWidget *parent = nullptr);
    void applyConfigs(nmeaData *data);

private slots:
    // todo SLOT

private:
    void createLayout();

    QLabel *rotLabel;
    QLabel *durationLabel;

    RangeSlider *rotSlider;
    QComboBox *durationCombobox;


}