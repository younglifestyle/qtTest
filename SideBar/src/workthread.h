#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include "common.h"
#include "window.h"

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = 0);
    void run();
    void stop();

signals:
    void ramSignal();
    void diskSignal();
    void picSignal();
    void netSignal();
    void uartSignal();

private slots:
    void getTestFlg(int flg);

private:
    int flg;
    volatile bool stopped;

};

#endif // WORKTHREAD_H
