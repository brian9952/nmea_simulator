#include "aamdialog.h"
#include<QtWidgets>
#include<iostream>

AAMDialog::AAMDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();
    createConnection();
}

void AAMDialog::createLayout(){
    // create label and range slider
    acrLabel = new QLabel(tr("Radius Range:"));
    lowLabelValue = new QLabel(tr("0"));
    highLabelValue = new QLabel(tr("1"));

    // range slider config
    acrRangeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    acrRangeSlider->setLowerValue(0);
    acrRangeSlider->setUpperValue(100);

    // right label
    highLabelValue->setAlignment(Qt::AlignRight);

    // duration label
    durationLabel = new QLabel(tr("Duration: "));

    // duration combobox
    QString *labelStr;
    durationCombobox = new QComboBox();
    for(int i = 0; i < 60; i++){
        if(i % 5 == 0){
            labelStr = new QString(QString::number(i) + " seconds");
            durationCombobox->addItem(*labelStr);
        }
    }

    // push buttons
    addButton = new QPushButton(tr("Add"));
    cancelButton = new QPushButton(tr("Cancel"));

    // push buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *durationLayout = new QVBoxLayout;
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationCombobox);

    QHBoxLayout *valueLayout = new QHBoxLayout;
    valueLayout->addWidget(lowLabelValue);
    valueLayout->addWidget(highLabelValue);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(acrLabel);
    layout->addWidget(acrRangeSlider);
    layout->addLayout(valueLayout);
    layout->addLayout(durationLayout);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

void AAMDialog::applyConfigs(nmeaData *data){
    data->aam->arrivalCircleRadius_firstRange = 1.0 * acrRangeSlider->GetLowerValue() / 100;
    data->aam->arrivalCircleRadius_lastRange = 1.0 * acrRangeSlider->GetUpperValue() / 100;
}

void AAMDialog::createConnection(){
    // range slider signalling
    // low value
    connect(acrRangeSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(syncLowValue(int)));

    // high value
    connect(acrRangeSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(syncHighValue(int)));

    // close button
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

// SLOTS
void AAMDialog::syncLowValue(int val){
    float valConv = (float) val;
    valConv = valConv / 100;
    QString valStr;
    valStr.setNum(valConv);
    lowLabelValue->setText(valStr);
}

void AAMDialog::syncHighValue(int val){
    float valConv = (float) val;
    valConv = valConv / 100;
    QString valStr;
    valStr.setNum(valConv);
    highLabelValue->setText(valStr);
}
