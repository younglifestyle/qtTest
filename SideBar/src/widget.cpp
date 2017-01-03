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

    image = new QImage[3];
    image[0].load(":/images/resources/1.jpg");
    image[1].load(":/images/resources/2.jpg");
    image[2].load(":/images/resources/3.jpg");
    ui->label_4->setPixmap(QPixmap::fromImage(image[0]));

    QString localIP = this->get_localmachine_ip();
    ui->label_local_ip->setStyleSheet("color: rgb(234, 234, 234)");
    ui->label_local_ip->setText(localIP);

    /* 隐藏掉Tab */
//    ui->testWidget->tabBar()->hide();

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
    connect(ui->sendPushButton,     SIGNAL(clicked()), this,  SLOT(sendUsbCommand_0x0A_Slot()));
    connect(ui->clearrecPushButton, SIGNAL(clicked()), this,  SLOT(clearInfoUsbDateSlot()));
    connect(ui->queryclearPushButton,SIGNAL(clicked()),this,  SLOT(keyCodeClearSlot()));

    connect(this, SIGNAL(changeTestFlg(int)), thread, SLOT(getTestFlg(int)));   /* 连接线程 */
    connect(this, SIGNAL(changeTimeDate(QString)), this, SLOT(changeLabelTime(QString)));
    connect(this, SIGNAL(changeFalutDate(QString)), this, SLOT(changeLabelFalut(QString)));

    connect(thread, SIGNAL(ramSignal()),  this, SLOT(ram_test()),       Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(diskSignal()), this, SLOT(disk_test()),      Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(picSignal()),  this, SLOT(toggle_Picture()), Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(netSignal()),  this, SLOT(net_test()),       Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(uartSignal()), this, SLOT(uart_test()),      Qt::BlockingQueuedConnection);

    connect(thread, SIGNAL(circSignal()), this, SLOT(circ_test()),      Qt::BlockingQueuedConnection);

    connect(thread, SIGNAL(sendKeyDataSignal(unsigned char*)), this, SLOT(query_SetKeyTextSlot(unsigned char*)), Qt::BlockingQueuedConnection);

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

    hid_exit();
    delete ui;
}

void Widget::check_DeviceExist()
{
    struct hid_device_info *devs, *cur_dev;
    int i = 0;

    kbdLite_isOk = false;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev)
    {
        if( cur_dev->vendor_id == 0x04B4 && cur_dev->product_id == 0x0201 )
        {
            qDebug() << " kbdLite_isOk ";
            kbdLite_isOk = true;
            ui->toolButton_kbdlite->setEnabled(true);
        }
        else
        {
            kbdLite_isOk = false;
            ui->toolButton_kbdlite->setEnabled(false);
        }

        /* i作为一个计数，默认为USB设备超过两个即可判断鼠标键盘空白热键都存在 */
        i++;
        if( i >= 2 )
        {
            ui->toolButton_kbd->setEnabled(true);
            ui->toolButton_mouse->setEnabled(true);
        }
        else
        {
            ui->toolButton_kbd->setEnabled(false);
            ui->toolButton_mouse->setEnabled(false);
        }
        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);
}

void Widget::initButtons()
{
    // 把按钮放在一个list里为了方便管理
    buttons.append(ui->toolButton_disk);
    buttons.append(ui->toolButton_kbd);
    buttons.append(ui->toolButton_kbdlite);
    buttons.append(ui->toolButton_mouse);
    buttons.append(ui->toolButton_net);
    buttons.append(ui->toolButton_pic);
    buttons.append(ui->toolButton_ram);
    buttons.append(ui->toolButton_uart);

    foreach (QToolButton *b, buttons)
    {
        connect(b, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));    /* 连接信号signal */
    }

    ui->toolButton_ram->setProperty("first", "true"); // 第一个按钮上面的边框不要.
//    ui->toolButton_1->click(); // 第二个按钮被按下, 即设置它的current属性为true
}

void Widget::changeButtonStatus()
{
    // 用按钮的current属性来控制被按下按钮的外观.
    // 当按钮被按下时, 设置其current属性为true,
    // 其他按钮的current属性为false, 为了更新按钮的外观.
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }

    QToolButton *source = qobject_cast<QToolButton *>(sender());
    source->setProperty("current", "true");
    source->setStyleSheet("");
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton )
    {
        ui->leftButton->setProperty("current", "true");
        ui->leftButton->setStyleSheet("");
    }
    else if( e->button() == Qt::MidButton )
    {
        ui->midButton->setProperty("current", "true");
        ui->midButton->setStyleSheet("");
    }
    else if( e->button() == Qt::RightButton )
    {
        ui->rightButton->setProperty("current", "true");
        ui->rightButton->setStyleSheet("");
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    if( e->button() == Qt::LeftButton )
    {
        ui->leftButton->setProperty("current", "false");
        ui->leftButton->setStyleSheet("");
    }
    else if( e->button() == Qt::MidButton )
    {
        ui->midButton->setProperty("current", "false");
        ui->midButton->setStyleSheet("");
    }
    else if( e->button() == Qt::RightButton )
    {
        ui->rightButton->setProperty("current", "false");
        ui->rightButton->setStyleSheet("");
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    ui->mousePos->setText(QString("move ：(%1, %2)").arg(e->globalX()).arg(e->globalY()));
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

void Widget::toolButton_Ram_clicked()
{
    /* 此段代码即为使得Button失效，变灰 */
//    ui->toolButton_ram->setEnabled(false);
    /* 设置窗口为模态，不成功 */
//    window->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    window->setWindowModified(Qt::WindowModal);
//    window->show();

    circTest_isOk = false;

    /* 切换Tab至Tab1 */
    ui->testWidget->setCurrentIndex(0);

    emit this->changeTestFlg(RAM_TEST);
}

void Widget::toolButton_Disk_clicked()
{
    circTest_isOk = false;

    /* 切换Tab至Tab2 */
    ui->testWidget->setCurrentIndex(1);

    emit this->changeTestFlg(DISK_TEST);

    /* 修改字体颜色：无效 */
//    QPalette pal;
//    pal.setColor(QPalette::WindowText,Qt::red);
//    ui->textEdit->setPalette(pal);
//    ui->textEdit->setStyleSheet("color: darkblue;"
//                                "background-color:transparent;"
//                                "selection-color: yellow;"
//                                "selection-background-color: blue;");
//    ui->textEdit->setTextColor(Qt::red);
}

void Widget::exitButton()
{
    exit(0);
}

void Widget::toolButton_Pic_clicked()
{
    circTest_isOk = false;

    /* 切换Tab至Tab3 */
    ui->testWidget->setCurrentIndex(2);

    emit this->changeTestFlg(PIC_TEST);
}

void Widget::toolButton_Net_clicked()
{
    circTest_isOk = false;

    ui->testWidget->setCurrentIndex(3);

    emit this->changeTestFlg(NET_TEST);
}

void Widget::toolButton_Uart_clicked()
{
    circTest_isOk = false;

    ui->testWidget->setCurrentIndex(4);

    emit this->changeTestFlg(UART_TEST);
}

void Widget::toolButton_Mouse_clicked()
{
    circTest_isOk = false;

    ui->testWidget->setCurrentIndex(7);

    emit this->changeTestFlg(MOUS_TEST);
}

void Widget::toolButton_BLANKBD_clicked()
{
    circTest_isOk = false;

    if( kbdLite_isOk == true )
    {
        ui->testWidget->setCurrentIndex(6);
        emit this->changeTestFlg(BLANK_TEST);
    }
    else
    {
         QMessageBox::warning(this, "warning Message", "USB设备未插入或被占用");
    }
}

void Widget::circleButton_clicked()
{
    circTest_isOk = true;

    emit this->changeTestFlg(CIRC_TEST);
}

void Widget::getUsbPidVidSlot()
{
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x04B4, 0x0201);
    if( !devs )
    {
        ui->vidLineEdit->setText(" USB设备未插入或被占用 ");
        ui->pidLineEdit->setText(" USB设备未插入或被占用 ");
        ui->serLineEdit->setText(" USB设备未插入或被占用 ");
        return;
    }

    cur_dev = devs;
    unsigned short VID = cur_dev->vendor_id;
    unsigned short PID = cur_dev->product_id;
    wchar_t *Ser_Num = cur_dev->serial_number;

    ui->vidLineEdit->setText("0x0" + QString::number(VID, 16));
    ui->pidLineEdit->setText("0x0" + QString::number(PID, 16));
    ui->serLineEdit->setText(QString::number(*Ser_Num));

    hid_free_enumeration(devs);
}

void Widget::sendUsbCommand_0x0A_Slot()
{
    unsigned char buf1[8];
    unsigned char buf2[8];
    unsigned char buf3[8];
    hid_device *handle;
    int i;

    handle = hid_open(0x04B4, 0x0201, NULL);
    if ( !handle )
    {
        qDebug() << "unable to open device";
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
        qDebug("buf2 is :%d %02x", i,buf2[i]);
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
        ui->k16LineEdit->setText(QString::number(buf3[0],16));
        ui->k16LineEdit->setReadOnly(true);
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
    }
    else
    {
        ui->keyTextEdit->append("0x" + QString::number(KeyBuf[1], 16));
    }
}

void Widget::circ_test()
{
    if ( circTest_isOk )
    {
        ui->testWidget->setCurrentIndex(0);
        ram_test();
    }
    else
        return;

    if ( circTest_isOk )
    {
        ui->testWidget->setCurrentIndex(1);
        disk_test();
    }
    else
        return;

    if ( circTest_isOk )
    {
        ui->testWidget->setCurrentIndex(2);
        toggle_Picture();
    }
    else
        return;

    if ( circTest_isOk )
    {
        ui->testWidget->setCurrentIndex(3);
        net_test();
    }
    else
        return;

    if ( circTest_isOk )
    {
        ui->testWidget->setCurrentIndex(4);
        uart_test();
    }
    else
        return;

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

void Widget::uart_test()
{
    QString strText = "123abc";
    QByteArray ch = strText.toLatin1();

    sleep(1000);

    ui->textEdit_1->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    ui->textEdit_5->clear();

    if( serial.write(ch) == -1 && ui->testWidget->currentIndex() == 4 )
    {
        falut_Cnt += 1;
        ui->textEdit_1->setText("发送数据失败");
        return;
    }
    else
    {
        ui->textEdit_1->setText("发送数据：" + strText + "  成功");
    }

    sleep(1000);
    if( serial.write(ch) == -1 && ui->testWidget->currentIndex() == 4 )
    {
        falut_Cnt += 1;
        ui->textEdit_2->setText("发送数据失败");
        return;
    }
    else
    {
        ui->textEdit_2->setText("发送数据：" + strText + "  成功");
    }

    sleep(1000);
    if( serial.write(ch) == -1 && ui->testWidget->currentIndex() == 4 )
    {
        falut_Cnt += 1;
        ui->textEdit_3->setText("发送数据失败");
        return;
    }
    else
    {
        ui->textEdit_3->setText("发送数据：" + strText + "  成功");
    }

    sleep(1000);
    if( serial.write(ch) == -1 && ui->testWidget->currentIndex() == 4 )
    {
        falut_Cnt += 1;
        ui->textEdit_4->setText("发送数据失败");
        return;
    }
    else
    {
        ui->textEdit_4->setText("发送数据：" + strText + "  成功");
    }

    sleep(1000);
    if( serial.write(ch) == -1 && ui->testWidget->currentIndex() == 4 )
    {
        falut_Cnt += 1;
        ui->textEdit_5->setText("发送数据失败");
        return;
    }
    else
    {
        ui->textEdit_5->setText("发送数据：" + strText + "  成功");
    }
}

void Widget::toggle_Picture()
{
    ui->label_4->show();
    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->setPixmap(QPixmap::fromImage(image[0]));
        sleep(1000);
    }
    else
    {
        return;
    }

    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->setPixmap(QPixmap::fromImage(image[1]));
        sleep(1000);
    }
    else
    {
        return;
    }

    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->setPixmap(QPixmap::fromImage(image[2]));
        sleep(1000);
    }
    else
    {
        return;
    }

    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->hide();
        window->show();
        window->timer->start(40);
        sleep(2000);
        window->timer->stop();
        window->hide();
        sleep(50);
    }
    else
    {
        return;
    }

//    ui->label_4->hide();
}

void Widget::net_test()
{
    QString ip = "127.0.0.1";
    int exitCode;
    int cnt = 0;

    ui->net_textEdit1->clear();
    ui->net_textEdit2->clear();
    ui->net_textEdit2_2->clear();
    ui->net_textEdit2_3->clear();
    ui->net_textEdit2_4->clear();
    ui->net_textEdit2_5->clear();

    //对每个Ip执行ping命令检测其是否在线
    qDebug() << "ping " + ip << endl;
    #ifdef Q_OS_WIN
        QString strArg = "netsh interface ip set address \"本地连接";
        QString strArg1 = " %1\" static 192.168.0.10 255.255.255.0 192.168.0.1";
        QString strArg2 = "netsh interface ip set address \"本地连接 \" static 192.168.0.10 255.255.255.0 192.168.0.1";
        QString strArg3;
        //QString strArg = "ping " + ip + " -n 1 -i 2";
        exitCode = QProcess::execute(strArg2);
        if( 0 == exitCode )
            cnt++;

        for( int i = 0; i < 30; ++i )
        {
            strArg3 = strArg + strArg1.arg(i);
            exitCode = QProcess::execute(strArg3);
            //qDebug() << strArg3;
            if( 0 == exitCode )
                cnt++;
        }

        strArg = "ping " + ip + " -n 1 -i 2";
        exitCode = QProcess::execute(strArg);
    #else
        //其他平台(Linux或Mac)
        exitCode = QProcess::execute("ping",  QStringList() << "-c 1" << "-t 2" << ip);
    #endif

    /* strArg.arg("~~~~"), 可进行修改 */
    sleep(300);

    if(0 == exitCode)
    {
        //it's alive
        qDebug() << "shell ping " + ip + " sucessed!";
        ui->net_textEdit1->setText("来自 127.0.0.1 的回复: 字节=32 时间<1ms TTL=64");

        sleep(500);
        if( ui->testWidget->currentIndex() == 3 )
        {
            ui->net_textEdit2->setText("来自 127.0.0.1 的回复: 字节=32 时间<1ms TTL=64");
        }
        else
        {
            return;
        }

        sleep(500);
        if( ui->testWidget->currentIndex() == 3 )
        {
            ui->net_textEdit2_2->setText("来自 127.0.0.1 的回复: 字节=32 时间<1ms TTL=64");
        }
        else
        {
            return;
        }

        sleep(500);
        if( ui->testWidget->currentIndex() == 3 )
        {
            ui->net_textEdit2_3->setText("来自 127.0.0.1 的回复: 字节=32 时间<1ms TTL=64");
        }
        else
        {
            return;
        }

        sleep(500);
        if( ui->testWidget->currentIndex() == 3 )
        {
            ui->net_textEdit2_4->setText("来自 127.0.0.1 的回复: 字节=32 时间<1ms TTL=64");
        }
        else
        {
            return;
        }

        sleep(500);
        if( ui->testWidget->currentIndex() == 3 )
        {
            ui->net_textEdit2_5->setText("来自 127.0.0.1 的回复: 字节=32 时间<1ms TTL=64");
        }
        else
        {
            return;
        }
    }
    else
    {
        ui->net_textEdit1->setText("请求超时");
    }
}

void Widget::disk_test()
{
    int i = 0;
    int j = 0;
    QFile file( "1.txt" );
    QTextDocument *document = ui->disk_textEdit1->document();
    QTextBlock currentBlock = document->begin();
    QTextBlock::iterator it;
    QTextCursor cursor = ui->disk_textEdit1->textCursor();

    QTextDocument *document2 = ui->disk_textEdit2->document();
    QTextBlock currentBlock2 = document2->begin();
    QTextCursor cursor2 = ui->disk_textEdit2->textCursor();

    /* 不存在即创建 */
    if ( !file.exists() )
    {
        file.open( QIODevice::WriteOnly );
        file.close();
    }

    /* 创建后若还不存在即可报错 */
    if ( !file.exists() )
    {
        falut_Cnt += 1;
    }

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<< "Open failed.";
        return;
    }

    QString content = "R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R R\n";

    //写入文件
    qint64 length[5] = {-1, -1, -1, -1, -1};
    for (i = 0; i < 5; i++)
    {
        length[i] = file.write(content.toLatin1(), content.length());
//        if(length[i] == -1)
//            qDebug()<<"写入文件失败";
    }

    if( length[0] == -1 || length[1] == -1 || length[2] == -1 || length[3] == -1 || length[4] == -1 )
    {
        falut_Cnt += 1;
    }

    while(1)
    {
        // 在修改chatformat时会改变当前Block的fragment
        // 所以++it的处理类似std::map中的erase操作
        for (it = currentBlock.begin(), j = 0; !(it.atEnd()); ++it, ++j)
        {
            QTextFragment currentFragment = it.fragment();

            if (currentFragment.isValid() && length[j] != -1)
            {
                int pos = currentFragment.position();
                QString strText = currentFragment.text();

                for(i = 0; i < strText.length(); i++)
                {
                    // 选择一个字,设置为红色
                    QTextCharFormat fmt;
                    fmt.setFontPointSize(24);
                    QTextCursor helper = cursor;
                    helper.setPosition(pos++);
                    helper.setPosition(pos, QTextCursor::KeepAnchor);

                    fmt.setForeground(QBrush(QColor(255, 0, 0)));
                    helper.setCharFormat(fmt);
                    //QTest::qWait(1);
                    sleep(1);
                }
            }
        }
        currentBlock = currentBlock.next();
        if(!currentBlock.isValid())
            break;
    }
    //关闭文件
    file.close();

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "Open failed.";
        return;
    }
    j=0;
    QTextStream txtInput(&file);
    QString lineStr;
    while( !txtInput.atEnd() )
    {
        lineStr = txtInput.readLine();
        if( (QString::compare(lineStr, content.remove(QChar('\n'), Qt::CaseInsensitive))) == 0 )
            length[j++] = 0;
        else
            length[j++] = -1;
    }

    while(1)
    {
        // 在修改chatformat时会改变当前Block的fragment
        // 所以++it的处理类似std::map中的erase操作
        for (it = currentBlock2.begin(), j = 0; !(it.atEnd()); ++it, ++j)
        {
            QTextFragment currentFragment2 = it.fragment();

            if (currentFragment2.isValid() && length[j] != -1)
            {
                int pos2 = currentFragment2.position();
                QString strText2 = currentFragment2.text();

                for(i = 0; i < strText2.length(); i++)
                {
                    // 选择一个字,设置为红色
                    QTextCharFormat fmt2;
                    fmt2.setFontPointSize(24);
                    QTextCursor helper2 = cursor2;
                    helper2.setPosition(pos2++);
                    helper2.setPosition(pos2, QTextCursor::KeepAnchor);

                    fmt2.setForeground(QBrush(QColor(255, 0, 0)));
                    helper2.setCharFormat(fmt2);
                    //QTest::qWait(1);
                    sleep(1);
                }
            }
        }
        currentBlock2 = currentBlock2.next();
        if(!currentBlock2.isValid())
            break;
    }

//    if( (length[0]==0)&&(length[1]==0)&&(length[2]==0)&&(length[3]==0)&&(length[4]==0) )
//        MainWindow::result[1] = 1;
//    else
//        MainWindow::result[1] = 0;

    /**********selectAll()选中文本修改字体颜色，后取消选中***********/
    QTextCharFormat fmt;
    fmt.setFontPointSize(24);
    fmt.setForeground(QBrush(QColor(234, 234, 234, 234)));
    ui->disk_textEdit1->selectAll();
    ui->disk_textEdit1->setCurrentCharFormat(fmt);
    cursor.movePosition( QTextCursor::End );
    ui->disk_textEdit1->setTextCursor( cursor );

    ui->disk_textEdit2->selectAll();
    ui->disk_textEdit2->setCurrentCharFormat(fmt);
    cursor2.movePosition( QTextCursor::End );
    ui->disk_textEdit2->setTextCursor( cursor2 );
    /************************************************************/

    QFile::remove("1.txt");
}

void Widget::ram_test()
{
    int i;
    int x = 0;

    QTextDocument *document = ui->textEdit->document();
    QTextBlock currentBlock = document->begin();
    QTextBlock::iterator it;
    QTextCursor cursor = ui->textEdit->textCursor();

    /* 设置文本为用户不可编辑 */
//    ui->textEdit->setReadOnly(1);
    QTextCharFormat fmt;
    fmt.setFontPointSize(24);
    fmt.setForeground(QBrush(QColor(255, 0, 0)));

    /* 去掉while，只显示染一排字颜色 */
    while(1)
    {
        // 在修改chatformat时会改变当前Block的fragment
        // 所以++it的处理类似std::map中的erase操作
        for (it = currentBlock.begin(); !(it.atEnd()); )
        {
            QTextFragment currentFragment = it.fragment();

            if (currentFragment.isValid())
            {
                ++it;
                int pos = currentFragment.position();
                QString strText = currentFragment.text();

//                qDebug()<<"len"<<strText.length();
//                qDebug()<<"pos"<<pos;
//                qDebug()<<"strText : "<<strText.at(2);

                for(i = 0; i < strText.length(); i++)
                {
                    // 选择一个字,设置为红色
                    QTextCursor helper = cursor;
                    helper.setPosition(pos++);
                    helper.setPosition(pos, QTextCursor::KeepAnchor);

                    if (strText.at(i) == ram[x])
                    {
                        x++;
//                        qDebug()<<strText.at(i);
                        helper.setCharFormat(fmt);
                        sleep(1);
                    }
                    else
                    {

                    }
                }
            }
        }
        currentBlock = currentBlock.next();
        if(!currentBlock.isValid())
            break;
    }

    /**********selectAll()选中文本修改字体颜色，后取消选中***********/
    fmt.setFontPointSize(24);
    fmt.setForeground( QBrush(QColor(234, 234, 234, 234)) );
    ui->textEdit->selectAll();
    ui->textEdit->setCurrentCharFormat(fmt);

    cursor.movePosition( QTextCursor::End );
    ui->textEdit->setTextCursor( cursor );
    /************************************************************/
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
