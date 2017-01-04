#include "thread.h"
#include "hidapi.h"

#include <QDebug>


Thread::Thread()
{
    stopped = false;
}

void Thread::setMessage(const QString &messages)
{
    messagesStr = messages;
}

void Thread::stop()
{
    stopped = true;
}

void Thread::run()
{
    hid_device *handle;

    handle = hid_open(0x04B4, 0x0201, NULL);
    if(handle==NULL)
    {
        qDebug()<<"Unable to open device";
        return;
    }

    while(!stopped)
    {
        unsigned char buf1[17];


        int res;



        res = hid_read_timeout(handle, buf1, 8, 15);
//                res = hid_read(handle, buf1, 8);
        if(res == -1)
        {
            qDebug()<<"read is failed!" ;
            return;
        }

//        qDebug()<<messagesStr;
        qDebug()<<buf1[1];
        if( res == 0 )
        {
//            hid_close(handle);
            continue;
        }
        else
            emit sigLoopSignal(buf1);
    }
    stopped = false;
    std::cerr<<std::endl;

}
