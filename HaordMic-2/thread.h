#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <iostream>

using namespace std;

class Thread:public QThread
{
    Q_OBJECT
public:
    Thread();

    void setMessage(const QString &messages);
    void stop();
signals:
    void sigLoopSignal(unsigned char *pk);

private slots:
    void run();

private:
    QString messagesStr;
    volatile bool stopped;
};

#endif // THREAD_H
