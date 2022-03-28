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

void SendDataThreads::setAddedData(QVector<RunningData*> &ptr){
    dataFrontendPtr = ptr;
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
    if(dataFrontendPtr.length() == 0)
        return;

    for(int i = 0; i < dataFrontendPtr.length(); i++){
        if(dataObj->dataStatus[i]->isEnabled &&
                dataObj->dataStatus[i]->isAdded &&
                dataObj->dataStatus[i]->sec !=
                dataObj->dataStatus[i]->duration){

            switch(dataFrontendPtr[i]->id){
                case 0:
                    dataStr.append(dataObj->createAAMString());
                    break;
                case 1:
                    dataStr.append(dataObj->createBODString());
                    break;
                default:
                    break;
            }
            dataNum++;
            dataObj->dataStatus[i]->sec++;

        }else{
            dataFrontendPtr[i]->checkboxData->setChecked(false);
        }

        if(dataObj->dataLineNum > 10){
            removeTopLine();
        }else{
            dataObj->dataLineNum++;
        }

    }


    if(dataNum > 0){
        sendConsole->appendPlainText(dataStr);
    }
}
