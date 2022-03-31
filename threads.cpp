#include "threads.h"
#include "nmeadata.h"
#include <QtWidgets>
#include <iostream>

SendDataThreads::SendDataThreads(QPlainTextEdit *sendConsole_param,
                                 QObject *parent) :
    QObject(parent)
{
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

void SendDataThreads::printStatus(){
    for(int i = 0; i < dataObj->dataStatus.length(); i++){
        std::cout << dataObj->dataStatus[i]->dataNames.toStdString() << " Added = "
                  << dataObj->dataStatus[i]->isAdded << ", Enabled = "
                  << dataObj->dataStatus[i]->isEnabled << std::endl;
    }
}

int SendDataThreads::searchDataId(int index){
    for(int i = 0; i < dataObj->dataStatus.length(); i++){
        if(dataObj->dataStatus[i]->id == index){
            return i;
        }
    }
    return -1;
}

void SendDataThreads::setAddedData(QVector<RunningData*> &ptra, nmeaData *ptrb){
    dataFrontendPtr = ptra;
    dataObj = ptrb;
    //printStatus();
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
    //std::cout << dataFrontendPtr.length() << std::endl;
    if(dataFrontendPtr.length() == 0)
        return;

    for(int i = 0; i < dataFrontendPtr.length(); i++){
        // get data index
        int index = searchDataId(dataFrontendPtr[i]->id);
        if(dataObj->dataStatus[index]->isEnabled &&
                dataObj->dataStatus[index]->isAdded &&
                dataObj->dataStatus[index]->sec !=
                dataObj->dataStatus[index]->duration){

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
            dataObj->dataStatus[index]->sec++;

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
