#include <Dialogs/boddialog.h>
#include <QtWidgets>

BODDialog::BODDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();
    createConnection();
}

void BODDialog::createLayout(){
    // bdt
    bdtLabel = new QLabel(tr("Bearing Degrees True Range: "));
    bdtRangeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    bdtLowValue = new QLabel(tr("0"));
    bdtHighValue = new QLabel(tr("360"));
    bdtHighValue->setAlignment(Qt::AlignRight);

    bdtRangeSlider->setMaximum(360);

    QVBoxLayout *bdtLayout = new QVBoxLayout;
    bdtLayout->addWidget(bdtLabel);
    bdtLayout->addWidget(bdtRangeSlider);

    QHBoxLayout *bdtValueLayout = new QHBoxLayout;
    bdtValueLayout->addWidget(bdtLowValue);
    bdtValueLayout->addWidget(bdtHighValue);

    // bdm
    bdmLabel = new QLabel(tr("Bearing Degrees Magnitude Range: "));
    bdmRangeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    bdmLowValue = new QLabel(tr("0"));
    bdmHighValue = new QLabel(tr("360"));
    bdmHighValue->setAlignment(Qt::AlignRight);

    bdmRangeSlider->setMaximum(360);

    QVBoxLayout *bdmLayout = new QVBoxLayout;
    bdmLayout->addWidget(bdmLabel);
    bdmLayout->addWidget(bdmRangeSlider);

    QHBoxLayout *bdmValueLayout = new QHBoxLayout;
    bdmValueLayout->addWidget(bdmLowValue);
    bdmValueLayout->addWidget(bdmHighValue);

    // duration label
    durationLabel = new QLabel(tr("Duration: "));

    // duration combobox
    // duration combobox
    durationCombobox = new QComboBox;
    durationCombobox->addItem("30 Seconds");
    durationCombobox->addItem("1 Minutes");
    durationCombobox->addItem("5 Minutes");
    durationCombobox->addItem("10 Minutes");
    durationCombobox->addItem("30 Minutes");
    durationCombobox->addItem("60 Minutes");
    durationCombobox->addItem("Infinite");

    QVBoxLayout *durationLayout = new QVBoxLayout;
    durationLayout->addWidget(durationLabel);
    durationLayout->addWidget(durationCombobox);

    // buttons
    addButton = new QPushButton(tr("Apply"));
    cancelButton = new QPushButton(tr("Cancel"));

    // button layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(bdtLayout);
    mainLayout->addLayout(bdtValueLayout);
    mainLayout->addLayout(bdmLayout);
    mainLayout->addLayout(bdmValueLayout);
    mainLayout->addLayout(durationLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void BODDialog::createConnection(){
    // bdt range
    connect(bdtRangeSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(bdtSyncLowValue(int)));
    connect(bdtRangeSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(bdtSyncHighValue(int)));
    // bdm range
    connect(bdmRangeSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(bdmSyncLowValue(int)));
    connect(bdmRangeSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(bdmSyncHighValue(int)));

    // cancel button
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

void BODDialog::applyConfigs(nmeaData *data){
    // bearing degrees true
    data->bod->bearingDegreesTrue_firstRange = bdtRangeSlider->GetLowerValue();
    data->bod->bearingDegreesTrue_lastRange = bdtRangeSlider->GetUpperValue();

    // bearing degrees magnetic
    data->bod->bearingDegreesMagn_firstRange = bdmRangeSlider->GetLowerValue();
    data->bod->bearingDegreesMagn_lastRange = bdmRangeSlider->GetUpperValue();

    if(durationCombobox->currentText() == "30 Seconds"){
        data->bod->duration = 30;
    }else if(durationCombobox->currentText() == "1 Minutes"){
        data->bod->duration = 60;
    }else if(durationCombobox->currentText() == "5 Minutes"){
        data->bod->duration = 300;
    }else if(durationCombobox->currentText() == "10 Minutes"){
        data->bod->duration = 600;
    }else if(durationCombobox->currentText() == "30 Minutes"){
        data->bod->duration = 1800;
    }else if(durationCombobox->currentText() == "60 Minutes"){
        data->bod->duration = 3600;
    }else if(durationCombobox->currentText() == "Infinite"){
        data->bod->duration = -1;
    }

}

// slots
void BODDialog::bdtSyncLowValue(int val){
    QString valStr;
    valStr.setNum(val);
    bdtLowValue->setText(valStr);
}

void BODDialog::bdtSyncHighValue(int val){
    QString valStr;
    valStr.setNum(val);
    bdtHighValue->setText(valStr);
}

void BODDialog::bdmSyncLowValue(int val){
    QString valStr;
    valStr.setNum(val);
    bdmLowValue->setText(valStr);
}

void BODDialog::bdmSyncHighValue(int val){
    QString valStr;
    valStr.setNum(val);
    bdmHighValue->setText(valStr);
}
