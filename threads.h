#ifndef THREADS_H
#define THREADS_H

#include <QObject>
#include <QVector>

class QPlainTextEdit;
class QTimer;
class QThread;
class QLabel;
class QCheckBox;
class nmeaData;

class SendDataThreads: public QObject
{
    Q_OBJECT
public:
    explicit SendDataThreads(QPlainTextEdit *sendConsole_param, nmeaData *dataObj_param, QObject *parent = nullptr);
    void setAddedData(QVector<int> &addedDataId_param);

private slots:
    void startTimer();
    void sendData();
    void removeTopLine();

private:
    QPlainTextEdit *sendConsole;
    QTimer *timer;
    QThread *thread;

    // data identification
    QVector<int> addedDataId;

    // nmea data obj
    nmeaData *dataObj;


};

#endif // THREADS_H
