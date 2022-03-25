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

void SendDataThreads::removeTopLine(){
    QTextCursor cursor = sendConsole->textCursor();
    cursor.movePosition(QTextCursor::Start);
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.removeSelectedText();
    cursor.deleteChar();
}

void SendDataThreads::sendData(){
    QString dataStr;
    int dataNum = 0;
    if(addedDataId.length() == 0)
        return;

    dataStr.append("===== Sending Data =====\n\n");

    std::cout << addedDataId.length() << std::endl;

    for(int i = 0; i < addedDataId.length(); i++){
        switch(addedDataId.at(i)){
            case 0:
                std::cout << "sending aam = " <<
                          dataObj->dataStatus[0]->isEnabled << " = " << i << std::endl;
                if(dataObj->dataStatus[0]->isEnabled &&
                        dataObj->dataStatus[0]->isAdded &&
                        dataObj->dataStatus[0]->sec <= dataObj->dataStatus[0]->duration){
                    dataStr.append(dataObj->createAAMString());
                    dataNum++;
                    dataObj->dataStatus[0]->sec++;
                }
                break;
            case 1:
                std::cout << "sending bod = " <<
                          dataObj->dataStatus[1]->isEnabled << " = " << i << std::endl;
                if(dataObj->dataStatus[1]->isEnabled &&
                        dataObj->dataStatus[1]->isAdded &&
                        dataObj->dataStatus[1]->sec <= dataObj->dataStatus[1]->duration){
                    dataStr.append(dataObj->createBODString());
                    dataNum++;
                    dataObj->dataStatus[1]->sec++;
                }
            default:
                break;
        }

        if(dataObj->dataLineNum > 10){
            std::cout << "HELLO" << std::endl;
            removeTopLine();
        }else{
            dataObj->dataLineNum++;
        }


    if(dataNum > 0){
        dataStr.append("===== Data Sent =====\n");
        sendConsole->appendPlainText(dataStr);
    }
    }
}
