#ifndef AAMDIALOG_H
#define AAMDIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>
#include "nmeadata.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QSignalMapper;

class AAMDialog : public QDialog
{

    Q_OBJECT

public:
    AAMDialog(QWidget *parent = nullptr);

    // public buttons;
    QPushButton *addButton;
    QPushButton *cancelButton;

    // functions
    void applyConfigs(nmeaData *data);

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
    QLabel *durationLabel;
    QComboBox *durationCombobox;

};

#endif // AAMDIALOG_H
