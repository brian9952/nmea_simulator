#ifndef THREADS_H
#define THREADS_H

#include <QObject>
#include <QVector>
#include "nmeadata.h"

class QPlainTextEdit;
class QTimer;
class QThread;
class QLabel;
class QPushButton;
class QCheckBox;

struct RunningData {
    int id;
    QLabel *labelData;
    QCheckBox *checkboxData;
    QPushButton *cancelButton;
};

class SendDataThreads: public QObject
{
    Q_OBJECT
public:
    explicit SendDataThreads(QPlainTextEdit *sendConsole_param, QObject *parent = nullptr);
    void setAddedData(QVector<RunningData*> &ptra, nmeaData *ptrb);

private slots:
    void startTimer();
    void sendData();
    void removeTopLine();

private:
    QPlainTextEdit *sendConsole;
    QTimer *timer;
    QThread *thread;

    // data identification
    QVector<RunningData*> dataFrontendPtr;

    // nmea data obj
    nmeaData *dataObj;

    void printStatus();
    int searchDataId(int index);

};

#endif // THREADS_H
