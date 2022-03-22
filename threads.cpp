#include "threads.h"
#include <QtWidgets>

SendDataThreads::SendDataThreads(QPlainTextEdit *sendConsole_param,
                                 QObject *parent) :
    QObject(parent)
{
    sendConsole = sendConsole_param;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SendDataThreads::sendData);

    thread = new QThread(parent);
    connect(thread, SIGNAL(started()),
            this, SLOT(executeTimer()));
    this->moveToThread(thread);
    thread->start();
}

void SendDataThreads::executeTimer(){
    timer->start(1000);
}

void SendDataThreads::sendData(){
    sendConsole->appendPlainText("WOLOLO");
}
