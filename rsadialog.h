#ifndef RSADIALOG_H
#define RSADIALOG_H

#include "libs/RangeSlider.h"
#include <QDialog>
#include "nmeadata.h"

class QPushButton;
class QLabel;
class QComboBox;

class RSADialog : public QDialog
{

    Q_OBJECT

public:
    RSADialog(QWidget *parent = nullptr);
    void applyConfigs(nmeaData *data);

    // apply button
    QPushButton *addButton;

private slots:
    void syncSrLowVal(int);
    void syncSrHighVal(int);
    void syncPrLowVal(int);
    void syncPrHighVal(int);

private:
    void createLayout();
    void createConnection();

    QLabel *srLowVal;
    QLabel *srHighVal;
    QLabel *prLowVal;
    QLabel *prHighVal;

    RangeSlider *srSlider;
    RangeSlider *prSlider;

    QComboBox *durationCombobox;
    QPushButton *cancelButton;
};

#endif // RSADIALOG_H
