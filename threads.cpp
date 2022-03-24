#include "threads.h"
#include "nmeadata.h"
#include <QtWidgets>
#include <iostream>

SendDataThreads::SendDataThreads(QPlainTextEdit *sendConsole_param,
                                 nmeaData *dataObj_param,
                                 QObject *parent) :
    QObject(parent)
{
    dataObj = dataObj_param;
    sendConsole = sendConsole_param;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SendDataThreads::sendData);

    thread = new QThread(parent);
    connect(thread, SIGNAL(started()), this, SLOT(startTimer()));
    this->moveToThread(thread);
    thread->start();
}

void SendDataThreads::startTimer(){
    timer->start(1000);
}

void SendDataThreads::setAddedData(QVector<int> &addedDataId_param){
    addedDataId = addedDataId_param;
}

void SendDataThreads::sendData(){
    QString dataStr;
    int dataNum = 0;
    if(addedDataId.length() == 0)
        return;

    std::cout << addedDataId.length() << std::endl;

    for(int i = 0; i < addedDataId.length(); i++){
        switch(addedDataId.at(i)){
            case 0:
                std::cout << "sending aam = " <<
                          dataObj->dataStatus[0]->isEnabled << " = " << i << std::endl;
                if(dataObj->dataStatus[0]->isEnabled &&
                        dataObj->dataStatus[0]->isAdded){
                    dataStr.append(dataObj->createAAMString());
                    dataNum++;
                }
                break;
            case 1:
                std::cout << "sending bod = " <<
                          dataObj->dataStatus[1]->isEnabled << " = " << i << std::endl;
                if(dataObj->dataStatus[1]->isEnabled &&
                        dataObj->dataStatus[1]->isAdded){
                    dataStr.append(dataObj->createBODString());
                    dataNum++;
                }
            default:
                break;
        }
    }

    if(dataNum > 0)
        sendConsole->appendPlainText(dataStr);
}
