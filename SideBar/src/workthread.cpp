#include "workthread.h"

#include <QDebug>

hid_device * myThread::handle = NULL;
bool myThread::KeyQuery_0A = false;

myThread::myThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
    flg = 16;

}

void myThread::run()
{
    int res;
    unsigned char buf1[20];

//    handle = hid_open(0x04B4, 0x0201, NULL);
//    if( !handle )
//    {
//        qDebug()<<"Unable to open device";
////        return;
//    }

    while( !stopped )
    {
        /* we call test code */
        switch (flg)
        {
            case RAM_TEST:
//                qDebug() <<" is ram_test ";
                emit this->ramSignal();
                break;

            case DISK_TEST:
//                qDebug() <<" is DISK_TEST ";
                emit this->diskSignal();
                break;

            case PIC_TEST:
//                qDebug() <<" is PIC_TEST ";
                emit this->picSignal();
                break;

            case NET_TEST:
//                qDebug() <<" is NET_TEST ";
                emit this->netSignal();
                break;

            case UART_TEST:
//                qDebug() <<" is NET_TEST ";
                emit this->uartSignal();
                break;

            case CIRC_TEST:
                emit this->circSignal();
                break;

            case MOUS_TEST:
                break;

            case BLANK_TEST:
                if( KeyQuery_0A )
                {
                    /* 获取状态查询码 */
                    buf1[0] = 0x0;
                    buf1[1] = 0x0A;

                    hid_write(this->handle, buf1, 2);

                    hid_read(this->handle, buf1,    8);
                    hid_read(this->handle, buf1+8,  8);
                    hid_read(this->handle, buf1+16, 1);

                    emit sendKeyQueryDataSignal(buf1);
                }

                res = hid_read_timeout(handle, buf1, 8, 30);
                if(res == -1)
                {
                    qDebug()<<"read is failed!";
                    emit sendKeyDataSignal(NULL);
                    continue;
                }
                if( res == 0 )
                {
                    continue;
                }
                else
                {
                    emit sendKeyDataSignal(buf1);
                }

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
//    qDebug() <<" is getTestFlg " << this->flg;
}

/* 使得run不执行循环操作 */
void myThread::stop()
{
    stopped = true;
}
