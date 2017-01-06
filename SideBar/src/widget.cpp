#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initButtons();

    QThread *thread1 = new QThread;

    falut_Cnt = 0;
    thread = new myThread(this);
    ram = new int[645];
    for(int i = 0; i < 645; i++)
        ram[i] = 'R';

    window = new Window(ui->tab_3);
    window->hide();
    window->setStyleSheet("background-color:transparent;");

//    window->moveToThread(thread);     /* 将该类移动到线程中，但是该类在主线程调用的函数还是会运行在主线程中 */

    pixmap = new QPixmap[3];
    image = new QImage[3];
    image[0].load(":/images/resources/1.jpg");
    image[1].load(":/images/resources/2.jpg");
    image[2].load(":/images/resources/3.jpg");
    ui->label_4->setPixmap(QPixmap::fromImage(image[0]));

    pixmap[0] = QPixmap::fromImage(image[0]);
    pixmap[1] = QPixmap::fromImage(image[1]);
    pixmap[2] = QPixmap::fromImage(image[2]);

    QString localIP = this->get_localmachine_ip();
    ui->label_local_ip->setStyleSheet("color: rgb(234, 234, 234)");
    ui->label_local_ip->setText(localIP);

    /* 隐藏掉Tab */
    ui->testWidget->tabBar()->hide();

    /* 先暂时在程序启动时显示第一个测试界面，后面可以直接hide testUI */
    ui->testWidget->setCurrentIndex(0);

    /* 去掉TextEdit的背景色，使其透明化 */
    ui->textEdit->setStyleSheet("background-color:transparent;");
    ui->disk_textEdit1->setStyleSheet("background-color:transparent;");
    ui->disk_textEdit2->setStyleSheet("background-color:transparent;");

    ui->net_textEdit1->setStyleSheet("color: rgb(234, 234, 234); background-color: rgb(25, 105, 154); font: bold; font-size : 24px");
    ui->net_textEdit2->setStyleSheet("color: rgb(234, 234, 234); background-color: rgb(25, 105, 154); font: bold; font-size : 24px");

    /* 设置按钮不可用 */
    ui->leftButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->midButton->setEnabled(false);
    setMouseTracking(true);

    /* 不让界面开始时跳那么一下 */
    ui->timeCnt->setText("00:00:00");
    ui->errorCnt->setText("0");

    /* 初始化串口 */
    initSeialPort();

    /* 检查USB设备、空白热键 */
    check_DeviceExist();

    connect(ui->toolButton_ram,     SIGNAL(clicked()), this,  SLOT(toolButton_Ram_clicked()));
    connect(ui->toolButton_disk,    SIGNAL(clicked()), this,  SLOT(toolButton_Disk_clicked()));
    connect(ui->toolButton_pic,     SIGNAL(clicked()), this,  SLOT(toolButton_Pic_clicked()));
    connect(ui->toolButton_net,     SIGNAL(clicked()), this,  SLOT(toolButton_Net_clicked()));
    connect(ui->toolButton_uart,    SIGNAL(clicked()), this,  SLOT(toolButton_Uart_clicked()));
    connect(ui->toolButton_mouse,   SIGNAL(clicked()), this,  SLOT(toolButton_Mouse_clicked()));
    connect(ui->toolButton_kbdlite, SIGNAL(clicked()), this,  SLOT(toolButton_BLANKBD_clicked()));
    connect(ui->exitButton,         SIGNAL(clicked()), this,  SLOT(exitButton()));

    connect(ui->circleButton,       SIGNAL(clicked()), this,  SLOT(circleButton_clicked()));

    connect(ui->getPushButton,      SIGNAL(clicked()), this,  SLOT(getUsbPidVidSlot()));
    connect(ui->clearrecPushButton, SIGNAL(clicked()), this,  SLOT(clearInfoUsbDateSlot()));
    connect(ui->queryclearPushButton,SIGNAL(clicked()),this,  SLOT(keyCodeClearSlot()));
    connect(ui->QueryCodePushButton, SIGNAL(clicked()), this,  SLOT(sendUsbCommand_0x0AFlg_Slot()));

    connect(this, SIGNAL(changeTestFlg(int)), thread, SLOT(getTestFlg(int)));   /* 连接线程 */
    connect(this, SIGNAL(changeTimeDate(QString)), this, SLOT(changeLabelTime(QString)));
    connect(this, SIGNAL(changeFalutDate(QString)), this, SLOT(changeLabelFalut(QString)));

    connect(thread, SIGNAL(ramSignal()),  this, SLOT(ram_test()),       Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(diskSignal()), this, SLOT(disk_test()),      Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(picSignal()),  this, SLOT(toggle_Picture()), Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(netSignal()),  this, SLOT(net_test()),       Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(uartSignal()), this, SLOT(uart_test()),      Qt::BlockingQueuedConnection);

    connect(thread, SIGNAL(circSignal()), this, SLOT(circ_test()),      Qt::BlockingQueuedConnection);

    connect(thread, SIGNAL(sendKeyDataSignal(unsigned char*)),  this,   SLOT(query_SetKeyTextSlot(unsigned char*)), Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(sendKeyQueryDataSignal(unsigned char*)), this,  SLOT(receive0x0AData_setText_Slot(unsigned char*)), Qt::BlockingQueuedConnection);

    this->thread->start();

    time = new QTime(0, 0, 0, 0);
//    time->start();                            /* 功能仅为：Sets this time to the current time */

    timer = new QTimer(0);
//    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()), Qt::DirectConnection);
    //connect(thread, SIGNAL(started()), timer,  SLOT(start()));
    timer->start(1000);
    timer->moveToThread(thread1);
    thread1->start();
}

Widget::~Widget()
{
    delete [] ram;
    delete [] image;
    delete timer;
    delete time;

    hid_close(myThread::handle);
    hid_exit();
    delete ui;
}

void Widget::check_DeviceExist()
{
    struct hid_device_info *devs, *cur_dev;
//    int i = 0;

    kbdLite_isOk = false;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;

    while (cur_dev)
    {
        if( cur_dev->vendor_id == 0x04B4 && cur_dev->product_id == 0x0201 )
        {            
            devInfo = *cur_dev;
            kbdLite_isOk = true;
//            ui->toolButton_kbdlite->setEnabled(true);
        }
        else
        {
            kbdLite_isOk = false;
        }

//        qDebug() << " kbdLite ";
        /* i作为一个计数，默认为USB设备超过两个即可判断鼠标键盘空白热键都存在 */
//        i++;
//        if( i >= 3 )
//        {
//            ui->toolButton_kbd->setEnabled(true);
//            ui->toolButton_mouse->setEnabled(true);
//        }
//        else
//        {
//            ui->toolButton_kbd->setEnabled(false);
//            ui->toolButton_mouse->setEnabled(false);
//        }
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);

    if( kbdLite_isOk )
    {
        myThread::handle = hid_open(0x04B4, 0x0201, NULL);
    }
}

void Widget::changeLabelTime(const QString &Tim)
{
    ui->timeCnt->setText(Tim);
}

void Widget::changeLabelFalut(const QString &date)
{
    ui->errorCnt->setText(date);
}

void Widget::onTimeout()
{
    static int oldCnt = 0;

    *time = time->addSecs(1);

    emit changeTimeDate(time->toString("hh:mm:ss"));

    if ( falut_Cnt != oldCnt )
    {
        oldCnt = falut_Cnt;
        emit changeFalutDate( QString::number(falut_Cnt) );
    }

//    qDebug() << "123" << time->toString("hh:mm:ss");

//    time->restart();
//    dateTime = QDateTime::fromTime_t(0, );
//    qDebug() << dateTime.toString("hh:mm:ss");
//    int totalSeconds = time->elapsed()/1000;
//    int seconds = totalSeconds % 60;
//    int minutes = (totalSeconds / 60) % 60;
//    int hours = totalSeconds / 3600;

//    qDebug() << "123" << time->elapsed()/1000.0 << totalSeconds << minutes << hours << seconds;
//                toString("hh:mm:ss");
    //ui->timeCnt->setText();
}

void Widget::getUsbPidVidSlot()
{
//    struct hid_device_info *devs, *cur_dev;

//    devs = hid_enumerate(0x04B4, 0x0201);
//    if( !devs )
//    {
//        ui->vidLineEdit->setText(" USB设备未插入或被占用 ");
//        ui->pidLineEdit->setText(" USB设备未插入或被占用 ");
//        ui->serLineEdit->setText(" USB设备未插入或被占用 ");
//        return;
//    }

//    struct hid_device_info *devs, *cur_dev;

//    devs = hid_enumerate(0x04B4, 0x0201);
//    cur_dev = devs;

    unsigned short VID = devInfo.vendor_id;
    unsigned short PID = devInfo.product_id;
    wchar_t *Ser_Num = devInfo.serial_number;

    ui->vidLineEdit->setText("0x0" + QString::number(VID, 16));
    ui->pidLineEdit->setText("0x0" + QString::number(PID, 16));
    ui->serLineEdit->setText(QString::number(*Ser_Num));

//    hid_free_enumeration(devs);
}

void Widget::receive0x0AData_setText_Slot(unsigned char *keyBuf)
{
    ui->k1LineEdit->setText("0x" + QString::number(keyBuf[1],16));
    ui->k2LineEdit->setText("0x" + QString::number(keyBuf[2],16));
    ui->k3LineEdit->setText("0x" + QString::number(keyBuf[3],16));
    ui->k4LineEdit->setText("0x" + QString::number(keyBuf[4],16));
    ui->k5LineEdit->setText("0x" + QString::number(keyBuf[5],16));
    ui->k6LineEdit->setText("0x" + QString::number(keyBuf[6],16));
    ui->k7LineEdit->setText("0x" + QString::number(keyBuf[7],16));

    ui->k8LineEdit->setText("0x" + QString::number(keyBuf[8],16));
    ui->k9LineEdit->setText("0x" + QString::number(keyBuf[9],16));
    ui->k10LineEdit->setText("0x" + QString::number(keyBuf[10],16));
    ui->k11LineEdit->setText("0x" + QString::number(keyBuf[11],16));
    ui->k12LineEdit->setText("0x" + QString::number(keyBuf[12],16));
    ui->k13LineEdit->setText("0x" + QString::number(keyBuf[13],16));
    ui->k14LineEdit->setText("0x" + QString::number(keyBuf[14],16));
    ui->k15LineEdit->setText("0x" + QString::number(keyBuf[15],16));

    ui->k16LineEdit->setText("0x" + QString::number(keyBuf[16],16));
}

void Widget::sendUsbCommand_0x0AFlg_Slot()
{
    if( myThread::KeyQuery_0A == false )
    {
        myThread::KeyQuery_0A = true;
    }
}

void Widget::clearInfoUsbDateSlot()
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
    return;
}

void Widget::keyCodeClearSlot()
{
    ui->keyTextEdit->clear();
}

void Widget::query_SetKeyTextSlot(unsigned char *KeyBuf)
{
    if( KeyBuf == NULL )
    {
        ui->keyTextEdit->append(" can not read the key data! ");
        return;
    }
    else
    {
        ui->keyTextEdit->append("0x" + QString::number(KeyBuf[1], 16));
    }
}

void Widget::sleep(unsigned int msec)
{
    QElapsedTimer t;
    t.start();

    while(t.elapsed() < msec)
        QCoreApplication::processEvents();

#if 0
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 20);
#endif
}

void Widget::initSeialPort()
{
    //获取计算机上所有串口并添加到comboBox中
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    if(infos.isEmpty())
    {
        ui->comboBox->addItem("无串口");
        return;
    }
    foreach (QSerialPortInfo info, infos)
    {
        ui->comboBox->addItem(info.portName());
        //qDebug() << info.portName();
    }
}

QString Widget::get_localmachine_ip()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if ( ipAddress.isEmpty() )
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    return ipAddress;
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSerialPortInfo info;
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    int i = 0;
    foreach(info, infos)
    {
        if(info.portName() == arg1)
            break;
        i++;
    }

//    qDebug() << info.portName();
//    qDebug() << infos.size();

    if(i != infos.size())
    {
        //can find
        ui->uart_label->setText("串口打开成功");
        serial.close();
        serial.setPort(info);
        if( serial.open(QIODevice::ReadWrite) )          //读写打开
            ui->uart_label->setText("串口打开成功");
        else
            ui->uart_label->setText("串口打开失败");
        serial.setBaudRate(QSerialPort::Baud115200);  //波特率
        serial.setDataBits(QSerialPort::Data8);     //数据位
        serial.setParity(QSerialPort::NoParity);    //无奇偶校验
        serial.setStopBits(QSerialPort::OneStop);   //一停止位
        serial.setFlowControl(QSerialPort::NoFlowControl);  //无控制
    }
    else
    {
        serial.close();
        ui->uart_label->setText("串口打开失败");
    }
}
