#include "aamdialog.h"
#include<QtWidgets>

AAMDialog::AAMDialog(QWidget *parent) : QDialog(parent)
{
    createLayout();

}

void AAMDialog::createLayout(){
    hello = new QLabel(tr("Hello World!"));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(hello);
    setLayout(layout);
}
