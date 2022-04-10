#include "dptdialog.h"
#include <QtWidgets>
#include <iostream>

DPTDialog::DPTDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();
    createConnection();
}

void DPTDialog::createLayout(){
    // water depth labels
    wdLabel = new QLabel("Water Depth: ");
    wdLowVal = new QLabel("0");
    wdHighVal = new QLabel("100");
    wdHighVal->setAlignment(Qt::AlignRight);

    // wd range slider
    wdSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    wdSlider->setLowerValue(0);
    wdSlider->setUpperValue(100);

    // max range labels
    maxRangeLabel = new QLabel("Max Range: ");
    maxRangeLowVal = new QLabel("-100");
    maxRangeHighVal = new QLabel("100");
    maxRangeHighVal->setAlignment(Qt::AlignRight);

    // max range range slider
    maxRangeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    maxRangeSlider->setLowerValue(0);
    maxRangeSlider->setUpperValue(100);

    // duration
    durationLabel = new QLabel("Duration: ");
    durationCombobox = new QComboBox;
    durationCombobox->addItem("30 Seconds", QVariant(30));
    durationCombobox->addItem("1 Minutes", QVariant(60));
    durationCombobox->addItem("5 Minutes", QVariant(300));
    durationCombobox->addItem("10 Minutes", QVariant(600));
    durationCombobox->addItem("30 Minutes", QVariant(1800));
    durationCombobox->addItem("60 Minutes", QVariant(3600));
    durationCombobox->addItem("Infinite", QVariant(-1));

    // wd Layout
    QHBoxLayout *wdValues = new QHBoxLayout;
    wdValues->addWidget(wdLowVal);
    wdValues->addWidget(wdHighVal);

    QVBoxLayout *wdLayout = new QVBoxLayout;
    wdLayout->addWidget(wdLabel);
    wdLayout->addWidget(wdSlider);
    wdLayout->addLayout(wdValues);

    // max range layout
    QHBoxLayout *maxRangeValues = new QHBoxLayout;
    maxRangeValues->addWidget(maxRangeLowVal);
    maxRangeValues->addWidget(maxRangeHighVal);

    QVBoxLayout *maxRangeLayout = new QVBoxLayout;
    maxRangeLayout->addWidget(maxRangeLabel);
    maxRangeLayout->addWidget(maxRangeSlider);
    maxRangeLayout->addLayout(maxRangeValues);

    // duration layout
    QVBoxLayout *durationLayout = new QVBoxLayout;
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationCombobox);

    // buttons
    addButton = new QPushButton(tr("Add"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(cancelButton);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(wdLayout);
    mainLayout->addLayout(maxRangeLayout);
    mainLayout->addLayout(durationLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

}

float DPTDialog::convMrValue(int val){
    float oldRange = 100 - 0;
    float newRange = 100 - (-100);
    return (((val - 0) * newRange) / oldRange) + (-100);
}

void DPTDialog::applyConfigs(nmeaData *data){
    // wd
    data->dpt->waterDepth_firstRange = wdSlider->GetLowerValue();
    data->dpt->waterDepth_lastRange = wdSlider->GetUpperValue();

    // max range
    data->dpt->maxRange_firstRange = convMrValue(maxRangeSlider->GetLowerValue());
    data->dpt->maxRange_lastRange = convMrValue(maxRangeSlider->GetUpperValue());

    // duration
    data->dpt->duration = durationCombobox->currentData().toInt();
}

void DPTDialog::createConnection(){
    // wd range
    connect(wdSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(wdSyncLowValue(int)));
    connect(wdSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(wdSyncHighValue(int)));

    // max range
    connect(maxRangeSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(mrSyncLowValue(int)));
    connect(maxRangeSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(mrSyncHighValue(int)));

    // cancel button
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

void DPTDialog::wdSyncLowValue(int val){
    QString valStr;
    valStr.setNum(val);
    wdLowVal->setText(valStr);
}

void DPTDialog::wdSyncHighValue(int val){
    QString valStr;
    valStr.setNum(val);
    wdHighVal->setText(valStr);
}

void DPTDialog::mrSyncLowValue(int val){
    QString valStr;
    valStr.setNum(convMrValue(val));
    maxRangeLowVal->setText(valStr);
}

void DPTDialog::mrSyncHighValue(int val){
    QString valStr;
    valStr.setNum(convMrValue(val));
    maxRangeHighVal->setText(valStr);
}
