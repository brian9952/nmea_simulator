#include "dptdialog.h"
#include <QtWidgets>

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

    // wd range slider
    wdSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    wdSlider->setLowerValue(0);
    wdSlider->setUpperValue(100);;

    // max range labels
    maxRangeLabel = new QLabel("Max Range: ");
    maxRangeLowVal = new QLabel("-100");
    maxRangeHighVal = new QLabel("100");

    // max range range slider
    maxRangeSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
    maxRangeSlider->setLowerValue(-100);
    maxRangeSlider->setUpperValue(100);

    // duration
    durationLabel = new QLabel("Duration: ");
    durationCombobox = new QComboBox;
    durationCombobox->addItem("30 Seconds");
    durationCombobox->addItem("1 Minutes");
    durationCombobox->addItem("5 Minutes");
    durationCombobox->addItem("10 Minutes");
    durationCombobox->addItem("30 Minutes");
    durationCombobox->addItem("60 Minutes");
    durationCombobox->addItem("Infinite");

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
    maxRangeValues->addWidget(maxRangeLowVal);

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

}

void DPTDialog::createConnection(){

}
