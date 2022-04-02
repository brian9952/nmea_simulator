#include "threads.h"
#include "nmeadata.h"
#include <QtWidgets>
#include <iostream>
#include <QSerialPort>

SendDataThreads::SendDataThreads(QPlainTextEdit *sendConsole_param,
                                 QStatusBar *status_param,
                                 QObject *parent) :
    QObject(parent)
{
    sendConsole = sendConsole_param;
    status = status_param;

    serial = new QSerialPort;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SendDataThreads::sendData);

    thread = new QThread(parent);
    connect(thread, SIGNAL(started()), this, SLOT(startTimer()));
    this->moveToThread(thread);
    thread->start();
}

void SendDataThreads::startTimer(){
    timer->start(5000);
}

void SendDataThreads::openSerialPort(){

    serial->setPortName(conf->portName);
    serial->setBaudRate(conf->baudRate);
    serial->setDataBits(conf->dataBits);
    serial->setParity(conf->parity);
    serial->setStopBits(conf->stopBits);
    serial->setFlowControl(conf->flowControl);

    if(serial->open(QIODevice::ReadWrite)){
        status->showMessage(QString("Connected to %1 : %2").arg(conf->portName).arg(QString::number(conf->baudRate)));
    }else{
        std::cout << serial->errorString().toStdString() << std::endl;
        status->showMessage(tr("Error Opening Port!"));
    }
}

void SendDataThreads::closeSerialPort(){
    serial->close();
    status->showMessage(tr("Disconnected"));
}

void SendDataThreads::printStatus(){
    for(int i = 0; i < dataObj->dataStatus.length(); i++){
        std::cout << dataObj->dataStatus[i]->dataNames.toStdString() << " Added = "
                  << dataObj->dataStatus[i]->isAdded << ", Enabled = "
                  << dataObj->dataStatus[i]->isEnabled << std::endl;
    }
}

void SendDataThreads::setPortConfigs(PortConfigs *conf_param){
    conf = conf_param;
    std::cout << conf->baudRate << std::endl;
    std::cout << conf->portName.toStdString() << std::endl;

    if(serial->isOpen())
        closeSerialPort();

    openSerialPort();
    // set conf
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

void SendDataThreads::sendSerial(QString &str){
    QByteArray br = str.toUtf8();
    serial->write(br);
}

void SendDataThreads::sendData(){
    QString dataStr;
    int dataNum = 0;
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

    }


    if(dataNum > 0){
        sendSerial(dataStr);
        sendConsole->appendPlainText(dataStr);
    }
}
