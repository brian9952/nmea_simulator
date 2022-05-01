#include <Dialogs/rsadialog.h>
#include <QtWidgets>
#include <iostream>

RSADialog::RSADialog(QWidget *parent) :
    QDialog(parent)
{
    createLayout();
    createConnection();
}

void RSADialog::createLayout(){

    // sr
    QLabel *srLabel = new QLabel("Starboard Sensor: ");
    srLowVal = new QLabel("0");
    srHighVal = new QLabel("180");
    srHighVal->setAlignment(Qt::AlignRight);

    // sr slider
    srSlider = new RangeSlider(Qt::Horizontal,
                               RangeSlider::Option::DoubleHandles,
                               nullptr);

    srSlider->setMinimum(0);
    srSlider->setMaximum(180);

    // pr
    QLabel *prLabel = new QLabel("Port Sensor: ");
    prLowVal = new QLabel("0");
    prHighVal = new QLabel("180");
    prHighVal->setAlignment(Qt::AlignRight);

    // pr slider
    prSlider = new RangeSlider(Qt::Horizontal,
                               RangeSlider::Option::DoubleHandles,
                               nullptr);

    prSlider->setMinimum(0);
    prSlider->setMaximum(180);

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
    addButton = new QPushButton(tr("Apply"));
    cancelButton = new QPushButton(tr("Cancel"));

    // sr layout
    QVBoxLayout *srLayout = new QVBoxLayout;
    srLayout->addWidget(srLabel);
    srLayout->addWidget(srSlider);

    // sr value
    QHBoxLayout *srValueLayout = new QHBoxLayout;
    srValueLayout->addWidget(srLowVal);
    srValueLayout->addWidget(srHighVal);

    // pr layout
    QVBoxLayout *prLayout = new QVBoxLayout;
    prLayout->addWidget(prLabel);
    prLayout->addWidget(prSlider);

    // pr value
    QHBoxLayout *prValueLayout = new QHBoxLayout;
    prValueLayout->addWidget(prLowVal);
    prValueLayout->addWidget(prHighVal);

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
    mainLayout->addLayout(srLayout);
    mainLayout->addLayout(srValueLayout);
    mainLayout->addLayout(prLayout);
    mainLayout->addLayout(prValueLayout);
    mainLayout->addLayout(durationLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void RSADialog::applyConfigs(nmeaData *data){
    // starboard rudder
    data->rsa->starboardRudder_firstRange = srSlider->GetLowerValue();
    data->rsa->starboardRudder_lastRange = srSlider->GetUpperValue();

    // port rudder
    data->rsa->portRudder_firstRange = prSlider->GetLowerValue();
    data->rsa->portRudder_lastRange = prSlider->GetUpperValue();

    // duration
    data->rsa->duration = durationCombobox->currentData().toInt();

}

void RSADialog::createConnection(){
    // sr
    connect(srSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(syncSrLowVal(int)));
    connect(srSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(syncSrHighVal(int)));

    // pr
    connect(prSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(syncPrLowVal(int)));
    connect(prSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(syncPrHighVal(int)));

    // cancel button
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

// slots
void RSADialog::syncSrLowVal(int val){
    QString valStr;
    valStr.setNum(val);
    srLowVal->setText(valStr);
}

void RSADialog::syncSrHighVal(int val){
    QString valStr;
    valStr.setNum(val);
    srHighVal->setText(valStr);
}

void RSADialog::syncPrLowVal(int val){
    QString valStr;
    valStr.setNum(val);
    prLowVal->setText(valStr);
}

void RSADialog::syncPrHighVal(int val){
    QString valStr;
    valStr.setNum(val);
    prHighVal->setText(valStr);
}
