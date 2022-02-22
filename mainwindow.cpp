#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    createLayout();

}

void MainWindow::createLayout(){
    window = new QWidget;
    toolbar = new QToolBar;

    // create toolbar
    toolbar->addAction("File");
    toolbar->addAction("Settings");
    toolbar->addAction("View");
    toolbar->addAction("About");
    toolbar->addAction("Help");



}

MainWindow::~MainWindow()
{
    delete ui;
}
