#include "workthread.h"

#include <QDebug>

hid_device * myThread::handle = NULL;
bool myThread::KeyQuery_0A = false;
bool myThread::circTest_isOk = false;
bool myThread::uart_Flg = true;
int myThread::checkBox_TestFlg[5] = {0};
int myThread::circle_Cnt = 0;

myThread::myThread(QObject *parent) :
    QThread(parent)
{
    stopped = false;
    flg = 16;
}

void myThread::run()
{
    int res;
    unsigned char buf1[17];
    unsigned char buf2[8];

    while( !stopped )
    {
        /* we call test code */
        switch (flg)
        {
            case RAM_TEST:
                emit this->ramSignal();
                break;

            case DISK_TEST:
                emit this->diskSignal();
                break;

            case PIC_TEST:
                emit this->picSignal();
                break;

            case NET_TEST:
                emit this->netSignal();
                break;

            case UART_TEST:
                emit this->uartSignal();
                break;

            case CIRC_TEST:
                if ( circTest_isOk )
                {
                    if ( checkBox_TestFlg[0] == true )
                    {
                        emit this->ramSignal();
                    }
                }

                if ( circTest_isOk )
                {
                    if ( checkBox_TestFlg[1] == true )
                    {
                        emit this->diskSignal();
                    }
                }

                if ( circTest_isOk )
                {
                    if ( checkBox_TestFlg[2] == true )
                    {
                        emit this->picSignal();
                    }
                }

                if ( circTest_isOk )
                {
                    if ( checkBox_TestFlg[3] == true )
                    {
                        emit this->netSignal();
                    }
                }

                if ( circTest_isOk )
                {
                    if ( checkBox_TestFlg[4] == true && uart_Flg == true )
                    {
                        emit this->uartSignal();
                    }
                }

                circle_Cnt += 1;
                break;

            case MOUS_TEST:
                /* 不需要线程协助 */
                break;

            case BLANK_TEST:
                memset(buf2, 0, sizeof(buf2));
                memset(buf1, 0, sizeof(buf1));

                res = hid_read_timeout(handle, buf2, 8, 60);
                if ( res == -1 )
                {
                    qDebug()<<"read is failed!";
                    emit sendKeyDataSignal(NULL);
                    continue;
                }
                if( res == 0 )
                {
//                    continue;
                }
                else
                {
                    emit sendKeyDataSignal(buf2);
                }

                if( KeyQuery_0A )
                {
                    /* 按下一次查询，只查询一次 */
                    KeyQuery_0A = false;

                    /* 获取状态查询码 */
                    buf1[0] = 0x0;
                    buf1[1] = 0x0A;

                    hid_write(this->handle, buf1, 2);

                    hid_read(this->handle, buf1,    8);
                    hid_read(this->handle, buf1+8,  8);
                    hid_read(this->handle, buf1+16, 1);

                    emit sendKeyQueryDataSignal(buf1);
                }

                break;

            default:
                break;
        }
    }

    stopped = false;   /* 为了下一次启动线程，重设标志位 */

    /* exec()执行后即是执行线程事件循环，控制权交给系统，但不会循环run exec();*/
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
