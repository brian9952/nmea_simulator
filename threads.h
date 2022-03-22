#ifndef THREADS_H
#define THREADS_H

#include <QObject>

class QPlainTextEdit;
class QTimer;
class QThread;

class SendDataThreads: public QObject
{
    Q_OBJECT
public:
    explicit SendDataThreads(QPlainTextEdit *sendConsole_param, QObject *parent = nullptr);

private slots:
    void executeTimer();
    void sendData();

private:
    QPlainTextEdit *sendConsole;
    QTimer *timer;
    QThread *thread;

signals:

};

#endif // THREADS_H
