#include "threads.h"
#include <QtWidgets>

SendDataThreads::SendDataThreads(QPlainTextEdit *sendConsole_param,
                                 QObject *parent) :
    QObject(parent)
{
    sendConsole = sendConsole_param;
    thread = new QThread(parent);
    this->moveToThread(thread);
    thread->start();
}

void SendDataThreads::sendData(QString &str){
    sendConsole->appendPlainText(str);
}
