#include "rotdialog.h"
#include <QtWidgets>
#include <iostream>

ROTDialog::ROTDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();
    createConnection();
}

void ROTDialog::createLayout(){
    rotLabel = new QLabel("Rate of Turn");
    rotLowVal = new QLabel("-100");
    rotHighVal = new QLabel("100");
    rotHighVal->setAlignment(Qt::AlignRight);

    // rot range slider
    rotSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    rotSlider->SetLowerValue(0);
    rotSlider->SetUpperValue(100);

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

    // buttons
    addButton = new QPushButton(tr("Add"));
    cancelButton = new QPushButton(tr("Cancel"));

    // rot layout
    QHBoxLayout *rotValues = new QHBoxLayout;
    rotValues->addWidget(rotLowVal);
    rotValues->addWidget(rotHighVal);

    // rot layout
    QVBoxLayout *rotLayout = new QVBoxLayout;
    rotLayout->addWidget(rotLabel);
    rotLayout->addWidget(rotSlider);
    rotLayout->addLayout(rotValues);

    // duration layout
    QVBoxLayout *durationLayout = new QVBoxLayout;
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationCombobox);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(cancelButton);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(rotLayout);
    mainLayout->addLayout(durationLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

float ROTDialog::convRotValue(int val){
    float oldRange = 100 - 0;
    float newRange = 100 + 100;
    return (((val - 0) * newRange) / oldRange) + (-100);
}

void ROTDialog::createConnection(){
    // rot range
    connect(rotSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(rotSyncLowValue(int)));
    connect(rotSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(rotSyncHighValue(int)));

    // cancel button
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

void ROTDialog::applyConfigs(nmeaData *data){
    // rot data
    data->rot->rateOfTurn_firstRange = convRotValue(rotSlider->GetLowerValue());
    data->rot->rateOfTurn_lastRange = convRotValue(rotSlider->GetUpperValue());

    // duration
    data->rot->duration = durationCombobox->currentData().toInt();
}

// slots
void ROTDialog::rotSyncLowValue(int val){
    QString valStr;
    valStr.setNum(convRotValue(val));
    rotLowVal->setText(valStr);
}

void ROTDialog::rotSyncHighValue(int val){
    QString valStr;
    valStr.setNum(convRotValue(val));
    rotHighVal->setText(valStr);
}
