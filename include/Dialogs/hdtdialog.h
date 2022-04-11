#ifndef HDTDIALOG_H
#define HDTDIALOG_H

#include <libs/RangeSlider/RangeSlider.h>
#include <QDialog>
#include <nmeadata.h>

class QPushButton;
class QLabel;
class QComboBox;

class HDTDialog : public QDialog
{

    Q_OBJECT

public:
    HDTDialog(QWidget *parent = nullptr);

    QPushButton *addButton;

    void applyConfigs(nmeaData *data);

private slots:
    void hdSyncLowVal(int);
    void hdSyncHighVal(int);

private:
    void createLayout();
    void createConnection();

    QLabel *hdLowVal;
    QLabel *hdHighVal;

    RangeSlider *hdSlider;

    QComboBox *durationCombobox;
    QPushButton *cancelButton;

};

#endif // HDTDIALOG_H
