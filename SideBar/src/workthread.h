#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include "common.h"
#include "hidapi.h"

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = 0);
    void run();
    void stop();

    static hid_device *handle;
    static bool circTest_isOk;
    static bool KeyQuery_0A;
    static bool uart_Flg;
    static int checkBox_TestFlg[5];
    static int circle_Cnt;

signals:
    void ramSignal();
    void diskSignal();
    void picSignal();
    void netSignal();
    void uartSignal();

    void sendKeyDataSignal(unsigned char *KeyBuf);
    void sendKeyQueryDataSignal(unsigned char *keyBuf);

private slots:
    void getTestFlg(int flg);

private:
    int flg;
    volatile bool stopped;

};

#endif // WORKTHREAD_H
