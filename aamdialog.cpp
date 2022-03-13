#include "aamdialog.h"
#include<QtWidgets>

AAMDialog::AAMDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();
    createConnection();
}

void AAMDialog::createLayout(){
    // create label and range slider
    acrLabel = new QLabel(tr("Radius Range:"));
    lowLabelValue = new QLabel(tr("0.0"));
    highLabelValue = new QLabel(tr("1.9"));
    acrRangeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);

    // right label
    highLabelValue->setAlignment(Qt::AlignRight);

    QHBoxLayout *valueLayout = new QHBoxLayout;
    valueLayout->addWidget(lowLabelValue);
    valueLayout->addWidget(highLabelValue);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(acrLabel);
    layout->addWidget(acrRangeSlider);
    layout->addLayout(valueLayout);

    setLayout(layout);
}

void AAMDialog::createConnection(){
    // range slider signalling
    // low value
    connect(acrRangeSlider, SIGNAL(lowerValueChanged(int)),
            this, SLOT(syncLowValue(int)));
    // high value
    connect(acrRangeSlider, SIGNAL(upperValueChanged(int)),
            this, SLOT(syncHighValue(int)));

}

// SLOTS
void AAMDialog::syncLowValue(int val){
    QString valStr;
    valStr.setNum(val);
    lowLabelValue->setText(valStr);
}

void AAMDialog::syncHighValue(int val){
    QString valStr;
    valStr.setNum(val);
    highLabelValue->setText(valStr);
}
