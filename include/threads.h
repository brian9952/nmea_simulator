#ifndef THREADS_H
#define THREADS_H

#include "datastructs.h"
#include <QObject>
#include <QVector>
#include "nmeadata.h"

class QPlainTextEdit;
class QTimer;
class QThread;
class QLabel;
class QPushButton;
class QCheckBox;

class SerialThreads: public QObject
{
    Q_OBJECT
public:
    explicit SerialThreads(QPlainTextEdit *sendConsole_param, QPlainTextEdit *receiveConsole_param, QStatusBar *status_param, QObject *parent = nullptr);
    void setAddedData(QVector<RunningData*> &ptra, nmeaData *ptrb);
    void updateConfigs();
    void setPortConfigs(PortConfigs *conf_param);
    void sendSerial(QString &str);

private slots:
    void startTimer();
    void sendData();
    void removeTopLine();
    void readData();

private:
    QPlainTextEdit *sendConsole;
    QPlainTextEdit *receiveConsole;
    QTimer *timer;
    QThread *thread;
    QStatusBar *status;

    // serial port
    QSerialPort *serial;

    // data identification
    QVector<RunningData*> dataFrontendPtr;

    // nmea data obj
    PortConfigs *conf;
    nmeaData *dataObj;

    void openSerialPort();
    void closeSerialPort();
    void printStatus();
    int searchDataId(int index);

};

#endif // THREADS_H
