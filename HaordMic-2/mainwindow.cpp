#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "thread.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(655,570);
    setMaximumSize(655,570);
    this->setWindowTitle("禾达芯微");
//    threadA.setMessage("Go for it!");

    QObject::connect(ui->getPushButton,SIGNAL(clicked(bool)),this,SLOT(getUsbDeviceSlot()));
    QObject::connect(ui->sendPushButton,SIGNAL(clicked(bool)),this,SLOT(sendUsbDateSlot()));
    QObject::connect(ui->clearrecPushButton,SIGNAL(clicked(bool)),this,SLOT(clearrecUsbDateSlot()));
    QObject::connect(ui->queryclearPushButton,SIGNAL(clicked(bool)),this,SLOT(keyClearSlot()));

    connect(ui->closeAllPushButton,SIGNAL(clicked(bool)),this,SLOT(quitSlot()));
    connect(ui->queryPushButton,SIGNAL(clicked(bool)),this,SLOT(startOrStopThreadA()));
    connect(&threadA,SIGNAL(sigLoopSignal(unsigned char *)),this,SLOT(keyOutDateSlot(unsigned char *)),Qt::BlockingQueuedConnection);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::getUsbDeviceSlot()
{
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x04B4, 0x0201);
    cur_dev = devs;

    unsigned short VID = cur_dev->vendor_id;
    unsigned short PID = cur_dev->product_id;
    wchar_t *Ser_Num = cur_dev->serial_number;

    ui->vidLineEdit->setText("0x0" + QString::number(VID, 16));
    ui->pidLineEdit->setText("0x0" + QString::number(PID, 16));
    ui->serLineEdit->setText(QString::number(*Ser_Num));

    hid_free_enumeration(devs);
}

void MainWindow::sendUsbDateSlot()
{
    unsigned char buf1[8];
    unsigned char buf2[8];
    unsigned char buf3[8];
    hid_device *handle;
    int i;

    handle = hid_open(0x04B4, 0x0201, NULL);
    if (!handle) {
        qDebug() << "unable to open device";
        printf("unable to open device\n");
        return;
    }
    // Set up the command buffer.
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(buf3, 0, sizeof(buf3));
    buf1[0] = 0x0;
    buf1[1] = 0x0A;

    hid_write(handle, buf1, 2);

    hid_read(handle, buf1, 8);
    hid_read(handle, buf2, 8);
    hid_read(handle, buf3, 1);

    hid_close(handle);

    // Print out the returned buffer.
    qDebug() << "Data read:";

    // Print out the returned buffer.
    for( i = 0; i < 8; i++ )
    {
        qDebug("buf1 is :%d %02x", i+1, buf1[i]);
        ui->k1LineEdit->setText(QString::number(buf1[1],16));
        ui->k2LineEdit->setText(QString::number(buf1[2],16));
        ui->k3LineEdit->setText(QString::number(buf1[3],16));
        ui->k4LineEdit->setText(QString::number(buf1[4],16));
        ui->k5LineEdit->setText(QString::number(buf1[5],16));
        ui->k6LineEdit->setText(QString::number(buf1[6],16));
        ui->k7LineEdit->setText(QString::number(buf1[7],16));
     }

    for( i = 0; i < 8; i++ )
    {
        qDebug("buf2 is :%d %02x", i+8, buf2[i]);
        ui->k8LineEdit->setText(QString::number(buf2[0],16));
        ui->k9LineEdit->setText(QString::number(buf2[1],16));
        ui->k10LineEdit->setText(QString::number(buf2[2],16));
        ui->k11LineEdit->setText(QString::number(buf2[3],16));
        ui->k12LineEdit->setText(QString::number(buf2[4],16));
        ui->k13LineEdit->setText(QString::number(buf2[5],16));
        ui->k14LineEdit->setText(QString::number(buf2[6],16));
        ui->k15LineEdit->setText(QString::number(buf2[7],16));
    }

    for (i = 0; i < 1; i++)
    {        
        qDebug("buf3 is :%d %02x", i+16, buf3[i]);
        ui->k16LineEdit->setText(QString::number(buf3[0],16));
    }
}

void MainWindow::clearrecUsbDateSlot()
{
    ui->k1LineEdit->clear();
    ui->k2LineEdit->clear();
    ui->k3LineEdit->clear();
    ui->k4LineEdit->clear();
    ui->k5LineEdit->clear();
    ui->k6LineEdit->clear();
    ui->k7LineEdit->clear();
    ui->k8LineEdit->clear();
    ui->k9LineEdit->clear();
    ui->k10LineEdit->clear();
    ui->k11LineEdit->clear();
    ui->k12LineEdit->clear();
    ui->k13LineEdit->clear();
    ui->k14LineEdit->clear();
    ui->k15LineEdit->clear();
    ui->k16LineEdit->clear();
    return ;
}



void MainWindow::keyClearSlot()
{
    ui->keyTextEdit->clear();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    threadA.stop();
    threadA.exit();
    e->accept();
}

void MainWindow::startOrStopThreadA()
{
    if(threadA.isRunning())
    {
        threadA.stop();
        ui->queryPushButton->setText("Start");
    }
    else
    {
        threadA.start();
        ui->queryPushButton->setText("停止");
    }
}

void MainWindow::quitSlot()
{
    exit(0) ;
}

void MainWindow::keyOutDateSlot(unsigned char *pq)
{
   ui->keyTextEdit->append("0x" + QString::number(pq[1],16));
   ui->keyTextEdit->setReadOnly(pq[1]);
}



