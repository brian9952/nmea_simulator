#include "hdtdialog.h"
#include <QtWidgets>
#include <iostream>

HDTDialog::HDTDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();
    createConnection();
}

void HDTDialog::createLayout(){
    // hd
    QLabel *hdLabel = new QLabel(tr("Heading: "));
    hdLowVal = new QLabel("0");
    hdHighVal = new QLabel("359");
    hdHighVal->setAlignment(Qt::AlignRight);

    // hd slider
    hdSlider = new RangeSlider(Qt::Horizontal,
                               RangeSlider::Option::DoubleHandles,
                               nullptr);
    hdSlider->setMinimum(0);
    hdSlider->setMaximum(359);

    // duration
    QLabel *durationLabel = new QLabel(tr("Duration: "));
    durationCombobox = new QComboBox;
    durationCombobox->addItem("30 Seconds", QVariant(30));
    durationCombobox->addItem("1 Minutes", QVariant(60));
    durationCombobox->addItem("5 Minutes", QVariant(300));
    durationCombobox->addItem("10 Minutes", QVariant(600));
    durationCombobox->addItem("30 Minutes", QVariant(1800));
    durationCombobox->addItem("60 Minutes", QVariant(3600));
    durationCombobox->addItem("Infinite", QVariant(-1));

    // buttons
    addButton = new QPushButton(tr("Add: "));
    cancelButton = new QPushButton(tr("Cancel: "));

    // hd val
    QHBoxLayout *hdValLayout = new QHBoxLayout;
    hdValLayout->addWidget(hdLowVal);
    hdValLayout->addWidget(hdHighVal);

    // hd layout
    QVBoxLayout *hdLayout = new QVBoxLayout;
    hdLayout->addWidget(hdLabel);
    hdLayout->addWidget(hdSlider);
    hdLayout->addLayout(hdValLayout);

    // duration layout
    QVBoxLayout *durationLayout = new QVBoxLayout;
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationCombobox);

    // button layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(cancelButton);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hdLayout);
    mainLayout->addLayout(durationLayout);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

}

void HDTDialog::applyConfigs(nmeaData *data){
    // hd
    data->hdt->heading_firstRange = hdSlider->GetLowerValue();
    data->hdt->heading_lastRange = hdSlider->GetUpperValue();

    // duration
    data->hdt->duration = durationCombobox->currentData().toInt();
}

void HDTDialog::createConnection(){
    // hd
    connect(hdSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(hdSyncLowVal(int)));
    connect(hdSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(hdSyncHighVal(int)));

    // cancel buttons
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

// SLOTS
void HDTDialog::hdSyncLowVal(int val){
    QString valStr;
    valStr.setNum(val);
    hdLowVal->setText(valStr);
}

void HDTDialog::hdSyncHighVal(int val){
    QString valStr;
    valStr.setNum(val);
    hdHighVal->setText(valStr);
}
