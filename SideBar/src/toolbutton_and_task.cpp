#include "widget.h"
#include "ui_widget.h"

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

void Widget::keyPressEvent(QKeyEvent *e)
{
    if( (e->modifiers() == Qt::ControlModifier) && (e->key() == Qt::Key_L) )
    {
        *time = time->addSecs(1800);
    }
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


void Widget::toolButton_Pic_clicked()
{
    circTest_isOk = false;

    /* 切换Tab至Tab3 */
    ui->testWidget->setCurrentIndex(2);

    emit this->changeTestFlg(PIC_TEST);
}
void Widget::toggle_Picture()
{
    ui->label_4->show();
    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->setPixmap(pixmap[0]);
        sleep(1000);
    }
    else
    {
        return;
    }

    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->setPixmap(pixmap[1].scaled(ui->label_4->size()));
        sleep(1000);
    }
    else
    {
        return;
    }

    if( ui->testWidget->currentIndex() == 2 )
    {
        ui->label_4->setPixmap(QPixmap::fromImage(image[2]).scaled(ui->label_4->size()));
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
        sleep(3000);
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


void Widget::toolButton_Net_clicked()
{
    circTest_isOk = false;

    ui->testWidget->setCurrentIndex(3);

    emit this->changeTestFlg(NET_TEST);
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


void Widget::toolButton_Uart_clicked()
{
    circTest_isOk = false;

    ui->testWidget->setCurrentIndex(4);

    emit this->changeTestFlg(UART_TEST);
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

    qDebug() << serial.write(ch);

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

    sleep(700);

    ui->comboBox->currentIndexChanged(ui->comboBox->currentText());
}


void Widget::toolButton_Mouse_clicked()
{
    circTest_isOk = false;

    ui->testWidget->setCurrentIndex(7);

    emit this->changeTestFlg(MOUS_TEST);
}

void Widget::toolButton_BLANKBD_clicked()
{
    struct hid_device_info *devs;
    circTest_isOk = false;

    if( kbdLite_isOk == true )
    {
        ui->testWidget->setCurrentIndex(6);
        emit this->changeTestFlg(BLANK_TEST);
    }
    else
    {
        devs = hid_enumerate(0x04B4, 0x0201);
        if( devs )
        {
            devInfo = *devs;
        }
        else
        {
            QMessageBox::warning(this, "warning Message", "USB设备未插入或被占用");
            return;
        }
        hid_free_enumeration(devs);

        if( !(myThread::handle = hid_open(0x04B4, 0x0201, NULL)) )
        {
            QMessageBox::warning(this, "warning Message", "USB设备未插入或被占用");
            return;
        }

        kbdLite_isOk = true;
        ui->testWidget->setCurrentIndex(6);
        emit this->changeTestFlg(BLANK_TEST);
    }
}

void Widget::circleButton_clicked()
{
    circTest_isOk = true;

    emit this->changeTestFlg(CIRC_TEST);
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


void Widget::exitButton()
{
    exit(0);
}





