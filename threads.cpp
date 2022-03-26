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
        switch(dataFrontendPtr[i]->id){
            case 0:
                std::cout << "sending aam = " <<
                          dataObj->dataStatus[0]->isEnabled << " = " << i << std::endl;
                if(dataObj->dataStatus[0]->isEnabled &&
                        dataObj->dataStatus[0]->isAdded &&
                        dataObj->dataStatus[0]->sec != dataObj->dataStatus[0]->duration){
                    dataStr.append(dataObj->createAAMString());
                    dataNum++;
                    dataObj->dataStatus[0]->sec++;
                }else{
                    dataFrontendPtr[i]->checkboxData->setChecked(false);
                }
                break;
            case 1:
                std::cout << "sending bod = " <<
                          dataObj->dataStatus[1]->isEnabled << " = " << i << std::endl;
                if(dataObj->dataStatus[1]->isEnabled &&
                        dataObj->dataStatus[1]->isAdded &&
                        dataObj->dataStatus[1]->sec != dataObj->dataStatus[1]->duration){
                    dataStr.append(dataObj->createBODString());
                    dataNum++;
                    dataObj->dataStatus[1]->sec++;
                }else{
                    dataFrontendPtr[i]->checkboxData->setChecked(false);
                }
            default:
                break;
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
