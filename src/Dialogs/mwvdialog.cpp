#include <Dialogs/mwvdialog.h>
#include <QtWidgets>
#include <iostream>

MWVDialog::MWVDialog(QWidget *parent) :
    QDialog(parent)
{
    createLayout();
    createConnection();
}

void MWVDialog::createLayout(){
    // wa
    QLabel *waLabel = new QLabel("Wind Angle:");
    waLowVal = new QLabel("0");
    waHighVal = new QLabel("359");
    waHighVal->setAlignment(Qt::AlignRight);

    // wa slider
    waSlider = new RangeSlider(Qt::Horizontal,
                               RangeSlider::Option::DoubleHandles,
                               nullptr);
    waSlider->SetMinimum(0);
    waSlider->SetMaximum(359);
    waSlider->SetLowerValue(0);
    waSlider->SetUpperValue(359);

    // ws
    QLabel *wsLabel = new QLabel("Wind Speed (Knots):");
    wsLowVal = new QLabel("0");
    wsHighVal = new QLabel("300");
    wsHighVal->setAlignment(Qt::AlignRight);

    // ws slider
    wsSlider = new RangeSlider(Qt::Horizontal,
                               RangeSlider::Option::DoubleHandles,
                               nullptr);
    wsSlider->SetMinimum(0);
    wsSlider->SetMaximum(300);
    wsSlider->SetLowerValue(0);
    wsSlider->SetUpperValue(300);

    // duration
    QLabel *durationLabel = new QLabel("Duration:");
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

    // wa layout
    QVBoxLayout *waLayout = new QVBoxLayout;
    waLayout->addWidget(waLabel);
    waLayout->addWidget(waSlider);

    // wa slider
    QHBoxLayout *waSliderLayout = new QHBoxLayout;
    waSliderLayout->addWidget(waLowVal);
    waSliderLayout->addWidget(waHighVal);

    // ws layout
    QVBoxLayout *wsLayout = new QVBoxLayout;
    wsLayout->addWidget(wsLabel);
    wsLayout->addWidget(wsSlider);

    // ws slider
    QHBoxLayout *wsSliderLayout = new QHBoxLayout;
    wsSliderLayout->addWidget(wsLowVal);
    wsSliderLayout->addWidget(wsHighVal);

    // duration layout
    QVBoxLayout *durationLayout = new QVBoxLayout;
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationCombobox);

    // button layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(waLayout);
    mainLayout->addLayout(waSliderLayout);
    mainLayout->addLayout(wsLayout);
    mainLayout->addLayout(wsSliderLayout);
    mainLayout->addLayout(durationLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void MWVDialog::applyConfigs(nmeaData *data){
    // wa slider
    data->mwv->windAngle_firstRange = waSlider->GetLowerValue();
    data->mwv->windAngle_lastRange = waSlider->GetUpperValue();

    // ws slider
    data->mwv->windSpeed_firstRange = wsSlider->GetLowerValue();
    data->mwv->windSpeed_lastRange = wsSlider->GetUpperValue();

    // duration
    data->mwv->duration = durationCombobox->currentData().toInt();
}

void MWVDialog::createConnection(){
    // wa
    connect(waSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(syncWaLowVal(int)));

    connect(waSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(syncWaHighVal(int)));

    // ws
    connect(wsSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(syncWsLowVal(int)));

    connect(wsSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(syncWsHighVal(int)));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

// slots
void MWVDialog::syncWaLowVal(int val){
    QString valStr;
    valStr.setNum(val);
    waLowVal->setText(valStr);
}

void MWVDialog::syncWaHighVal(int val){
    QString valStr;
    valStr.setNum(val);
    waHighVal->setText(valStr);
}

void MWVDialog::syncWsLowVal(int val){
    QString valStr;
    valStr.setNum(val);
    wsLowVal->setText(valStr);
}

void MWVDialog::syncWsHighVal(int val){
    QString valStr;
    valStr.setNum(val);
    wsHighVal->setText(valStr);
}
