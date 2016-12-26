#include "workthread.h"
#include "widget.h"
#include <QDebug>

myThread::myThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
    flg = 16;
}

void myThread::run()
{
    while( !stopped )
    {
        /* we call test code */
        switch (flg)
        {
            case RAM_TEST:
                qDebug() <<" is ram_test ";
                emit this->ramSignal();
                break;

            case DISK_TEST:
                qDebug() <<" is DISK_TEST ";
                emit this->diskSignal();
                break;

            case PIC_TEST:
                qDebug() <<" is PIC_TEST ";
                emit this->picSignal();
                break;

            case NET_TEST:
                qDebug() <<" is NET_TEST ";
                emit this->netSignal();
                break;

            default:
                break;
        }
    }

    stopped = false;   /* 为了下一次启动线程，重设标志位 */

    /* exec()执行后即是执行线程事件循环，控制权交给系统，但不会循环run */
    //    exec();
}

/* 连接主线程的signals */
void myThread::getTestFlg(int flg)
{
    this->flg = flg;
    qDebug() <<" is getTestFlg " << this->flg;
}

/* 使得run不执行循环操作 */
void myThread::stop()
{
    stopped = true;
}
