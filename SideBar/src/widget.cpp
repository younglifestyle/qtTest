#include "widget.h"
#include "ui_widget.h"

QPoint Widget::pos = QCursor::pos();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    fault_Cnt(0),
    ram(new int[40])
{
    ui->setupUi(this);

    setFocus();
    /* 初始化一些按键 */
    initButtons();

    clipboard = QApplication::clipboard();

    QThread *thread1 = new QThread;

    thread = new myThread(this);

    for(int i = 0; i < 40; i++)
        ram[i] = 'R';

    window = new Window(ui->tab_3);
    window->hide();
    window->setStyleSheet("background-color:transparent;");

//    window->moveToThread(thread);     /* 将该类移动到线程中，但是该类在主线程调用的函数还是会运行在主线程中 */

    faultfile = new QFile("faultLog.txt");
    cfgfile   = new QFile("config");

    readCfgText();

    pixmap = new QPixmap[3];
    image = new QImage[3];
    image[0].load(":/images/resources/1.jpg");
    image[1].load(":/images/resources/2.jpg");
    image[2].load(":/images/resources/3.jpg");
    ui->label_4->setPixmap(QPixmap::fromImage(image[0]));

    pixmap[0] = QPixmap::fromImage(image[0]);
    pixmap[1] = QPixmap::fromImage(image[1]);
    pixmap[2] = QPixmap::fromImage(image[2]);

//    QString localIP = this->get_localmachine_ip();
//    ui->label_local_ip->setStyleSheet("color: rgb(234, 234, 234)");
//    ui->label_local_ip->setText(localIP);

    /* 隐藏掉Tab */
    ui->testWidget->tabBar()->hide();
    ui->comboBox->hide();
    ui->label_3->setText(tr("欢迎进入XXX测试,请选择单项测试或循环测试"));
    ui->testWidget->setCurrentIndex(9);

    ui->mousePos->setText(QString("(%1, %2)").arg(pos.x()).arg(pos.y()));
//    /* 先暂时在程序启动时显示第一个测试界面，后面可以直接hide testUI */
//    ui->testWidget->setCurrentIndex(0);

    /* 去掉TextEdit的背景色，使其透明化 设置StyleSheet可以改变字体颜色以及背景色,可直接在UI界面上进行设置 */
//    ui->textEdit->setStyleSheet("background-color:transparent;");
//    ui->net_textEdit1->setStyleSheet("color: rgb(234, 234, 234); background-color: rgb(25, 105, 154); font: bold; font-size : 24px");

    /* 设置按钮不可用 */
    ui->leftButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->midButton->setEnabled(false);

    /* 键盘测试，设置按钮不可用可以让焦点保持在界面，消除BUG */
    ui->EscPushButton->setEnabled(false);

    ui->testWidget->setMouseTracking(true);

    /* 不让界面开始时跳那么一下 */
    ui->timeCnt->setText("00:00:00");
    ui->errorCnt->setText("0");

    /* 设置测试报告 */
    setfaultLogTextEdit();

    /* 初始化串口 */
    initSeialPort();

    /* 检查USB设备、空白热键 */
    check_DeviceExist();

    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    connect(ui->toolButton_ram,     SIGNAL(clicked()), this,  SLOT(toolButton_Ram_clicked()));
    connect(ui->toolButton_disk,    SIGNAL(clicked()), this,  SLOT(toolButton_Disk_clicked()));
    connect(ui->toolButton_pic,     SIGNAL(clicked()), this,  SLOT(toolButton_Pic_clicked()));
    connect(ui->toolButton_net,     SIGNAL(clicked()), this,  SLOT(toolButton_Net_clicked()));
    connect(ui->toolButton_uart,    SIGNAL(clicked()), this,  SLOT(toolButton_Uart_clicked()));
    connect(ui->toolButton_mouse,   SIGNAL(clicked()), this,  SLOT(toolButton_Mouse_clicked()));
    connect(ui->toolButton_kbdlite, SIGNAL(clicked()), this,  SLOT(toolButton_BLANKBD_clicked()));
    connect(ui->toolButton_kbd,     SIGNAL(clicked()), this,  SLOT(toolButton_KBD_clicked()));

    connect(ui->selectTestItemBtm,  SIGNAL(clicked()), this,  SLOT(selectTestItem_clicked()));
    connect(ui->circleButton,       SIGNAL(clicked()), this,  SLOT(circleButton_clicked()));

    connect(ui->getPushButton,      SIGNAL(clicked()), this,  SLOT(getUsbPidVidSlot()));
    connect(ui->clearrecPushButton, SIGNAL(clicked()), this,  SLOT(clearInfoUsbDateSlot()));
    connect(ui->queryclearPushButton,SIGNAL(clicked()),this,  SLOT(keyCodeClearSlot()));
    connect(ui->QueryCodePushButton, SIGNAL(clicked()), this,  SLOT(sendUsbCommand_0x0AFlg_Slot()));

    connect(this, SIGNAL(changeTestFlg(int)), thread, SLOT(getTestFlg(int)));   /* 连接线程 */
    connect(this, SIGNAL(changeTimeDate(QString)),  this, SLOT(changeLabelTime(QString)));
    connect(this, SIGNAL(changefaultDate(QString)), this, SLOT(changeLabelfault(QString)));
    connect(this, SIGNAL(changeCircleDate(QString)),this, SLOT(changeLableCircleDate(QString)));

    connect(thread, SIGNAL(ramSignal()),      this, SLOT(ram_test()),         Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(diskSignal()),     this, SLOT(disk_test()),        Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(picSignal()),      this, SLOT(toggle_Picture()),   Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(netSignal()),      this, SLOT(net_test()),         Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(uartSignal()),     this, SLOT(uart_test()),        Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(boardSignal(int)), this, SLOT(circleKBDTest(int)), Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(mouseSignal()),    this, SLOT(mouse_test()),       Qt::BlockingQueuedConnection);

    connect(ui->checkLogButton, SIGNAL(clicked()), this, SLOT(checkFaultLog_Slot()));
    connect(ui->deleteLogButton,SIGNAL(clicked()), this, SLOT(deleteFaultLog_Slot()));

    connect(thread, SIGNAL(sendKeyDataSignal(unsigned char*)),  this,   SLOT(query_SetKeyTextSlot(unsigned char*)), Qt::BlockingQueuedConnection);
    connect(thread, SIGNAL(sendKeyQueryDataSignal(unsigned char*)), this,  SLOT(receive0x0AData_setText_Slot(unsigned char*)), Qt::BlockingQueuedConnection);

    connect(this->clipboard, SIGNAL(dataChanged()), this, SLOT(changePrintButton()));

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
//    QStringList input = ui->textEdit_4->toPlainText().split("\n");

    /* 在退出整个程序时，将错误记录写入文件中保存 */
    if( ! inputFault.isEmpty() )
    {
        bool ok = faultfile->open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append );

        if ( ok )
        {
            QTextStream out(faultfile);
            foreach(QString s, inputFault)
            {
                out << s << endl;
            }
            faultfile->close();
        }
    }

    delete faultfile;
    delete [] ram;
    delete [] image;
//    delete timer;    /* 已经被移动到另外一个线程，无法在主线程进行关闭 */
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
            break;
        }
        else
        {
            kbdLite_isOk = false;
            qDebug() << kbdLite_isOk;
            break;
        }

        cur_dev = cur_dev->next;
    }

    hid_free_enumeration(devs);

    if( kbdLite_isOk )
    {
        myThread::handle = hid_open(0x04B4, 0x0201, NULL);
    }
}

void Widget::onTimeout()
{
    /*
     * timer这个类所生活的进程是在次线程中的，无法在主线程之外去操作任何界面控件
    */
    static int old_faultCnt = 0;
    static int old_circleCnt = 0;
    static int timeCnt = 0;
    static int dateOne = 0;

    timeCnt++;
    if( timeCnt >= 5 )
    {
        timeCnt = 0;
        infos = QSerialPortInfo::availablePorts();
        if( ! infos.isEmpty() )
        {
            myThread::uart_Flg = true;
        }
    }

    *time = time->addSecs(1);
    if ( time->toString("hh:mm:ss") != "23:59:59" )
    {
        if ( dateOne == 0 )
        {
            emit changeTimeDate(time->toString("hh:mm:ss"));
        }
        else
        {
            emit changeTimeDate("0" + QString::number(dateOne) + " " + time->toString("hh:mm:ss"));
        }
    }
    else
    {
        dateOne += 1;
        emit changeTimeDate("0" + QString::number(dateOne) + " " + time->toString("hh:mm:ss"));
    }

    if ( fault_Cnt != old_faultCnt )
    {
        old_faultCnt = fault_Cnt;
        emit changefaultDate( QString::number(fault_Cnt) );
    }

    if ( myThread::circle_Cnt != old_circleCnt )
    {
        old_circleCnt = myThread::circle_Cnt;
        emit changeCircleDate( QString::number(myThread::circle_Cnt) );
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

void Widget::sleep(unsigned int msec)
{
    QElapsedTimer t;
    t.start();

    while(t.elapsed() < msec)
        QCoreApplication::processEvents();

{
#if 0
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
#endif
}
}

void Widget::initSeialPort()
{
    //获取计算机上所有串口并添加到comboBox中
    infos = QSerialPortInfo::availablePorts();

    if ( infos.isEmpty() )
    {
        ui->uart_label->setText( tr("无串口") );
        myThread::uart_Flg = false;
        return;
    }

//    if(infos.isEmpty())
//    {
//        ui->comboBox->addItem("无串口");
//        return;
//    }
//    foreach (QSerialPortInfo info, infos)
//    {
//        ui->comboBox->addItem(info.portName());
//        //qDebug() << info.portName();
//    }
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSerialPortInfo info;
    int i = 0;

    /* 扫到最后一个，则停止扫描 */
    foreach(info, infos)
    {
        if(info.portName() == arg1)
            break;
        i++;
    }

//    qDebug() << info.portName();
//    qDebug() << infos.size();
//    qDebug() << i;

    if(i != infos.size())
    {
        //can find
        serial.close();
        serial.setPort(info);
        if( serial.open(QIODevice::ReadWrite) )                   //读写打开
        {
            ui->uart_label->setText(info.portName() + "打开成功");
        }
        else
        {
            ui->uart_label->setText(info.portName() + "打开失败");
            infos = QSerialPortInfo::availablePorts();
            return;
        }
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

void Widget::resizeEvent(QResizeEvent *event)
{
    int wd = window->width();
    int ht = window->height();

    window->move( (ui->testWidget->width() - wd) * 0.5, (ui->testWidget->height() - ht) * 0.4 );
    window->resize(600, 500);
}




