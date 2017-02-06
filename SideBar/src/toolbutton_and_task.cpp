#include "widget.h"
#include "ui_widget.h"

void Widget::toolButton_Ram_clicked()
{

{
    /* 此段代码即为使得Button失效，变灰 */
//    ui->toolButton_ram->setEnabled(false);
    /* 设置窗口为模态，不成功 */
//    window->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    window->setWindowModified(Qt::WindowModal);
//    window->show();
}
    /* 防止停止循环测试的功能 */
    myThread::circTest_isOk = false;

    /* 切换Tab至Tab1 */
    ui->testWidget->setCurrentIndex(0);
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    emit this->changeTestFlg(RAM_TEST);
}
void Widget::ram_test()
{
    int i = 0;

    ui->testWidget->setCurrentIndex(0);
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }
    ui->toolButton_ram->setProperty("current", "true");
    ui->toolButton_ram->setStyleSheet("");

    foreach (QPushButton *b, buttons_Ram)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }

    while ( ram[i] == 'R' )
    {
        buttons_Ram[i]->setProperty("current", "true");
        buttons_Ram[i]->setStyleSheet("");

        i++;

        if ( ui->testWidget->currentIndex() != 0 )
        {
            foreach (QPushButton *b, buttons_Ram)
            {
                b->setProperty("current", "false");
                b->setStyleSheet(""); // 刷新按钮的样式
            }
            return;
        }

        sleep(180);
    }

    if ( ram[i] != 'R' && i != RAM_CNT )
    {
        /* 记错标志 +1 */
        fault_Cnt += 1;

        /* 将要写入log文件中的字符串 */
        inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("内存测试失败！"));

        /* 将之显示到log TextEdit */
        ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("内存测试失败！"));
    }


{
#if 0
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
#endif
}
}


void Widget::toolButton_Disk_clicked()
{
    myThread::circTest_isOk = false;

    /* 切换Tab至Tab2 */
    ui->testWidget->setCurrentIndex(1);
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    emit this->changeTestFlg(DISK_TEST);

{
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
}
void Widget::disk_test()
{
    int i = 0;
    QFile file( "1.txt" );
    QFile::remove("1.txt");

    ui->testWidget->setCurrentIndex(1);
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }
    ui->toolButton_disk->setProperty("current", "true");
    ui->toolButton_disk->setStyleSheet("");

    foreach (QPushButton *b, buttons_Disk)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }

    /* 不存在即创建 */
    if ( !file.exists() )
    {
        file.open( QIODevice::WriteOnly );
        file.close();
    }
    /* 创建后若还不存在即可报错 */
    if ( !file.exists() )
    {
        fault_Cnt += 1;

        /* 将要写入log文件中的字符串 */
        inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));

        /* 将之显示到log TextEdit */
        ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));

        return;
    }

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        /* 发送错误，记错 */
        fault_Cnt += 1;

        /* 将要写入log文件中的字符串 */
        inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));

        /* 将之显示到log TextEdit */
        ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));
        return;
    }

    const char *content = "R";

    //写入文件
    qint64 length[24] = {-1, -1, -1, -1, -1};
    for (i = 0; i < 24; i++)
    {
        length[i] = file.write(content, qstrlen(content));
        if(length[i] != -1)
        {
            buttons_Disk[i]->setProperty("current", "true");
            buttons_Disk[i]->setStyleSheet("");

            if ( ui->testWidget->currentIndex() != 1 )
            {
                foreach (QPushButton *b, buttons_Disk)
                {
                    b->setProperty("current", "false");
                    b->setStyleSheet(""); // 刷新按钮的样式
                }
                return;
            }

            sleep(180);
        }
        else
        {
            /* 发送错误，记错 */
            fault_Cnt += 1;

            /* 将要写入log文件中的字符串 */
            inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));

            /* 将之显示到log TextEdit */
            ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));
        }
    }
    //关闭文件，使写操作生效
    file.close();


    /* 读文件 */
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        /* 打开失败也报错 */
        fault_Cnt += 1;

        ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));
        return;
    }

    i = 0;
    QTextStream txtInput(&file);
    QString lineStr;
    while( !txtInput.atEnd() )
    {
        lineStr = txtInput.readLine();
    }

    for ( i = 0; i < lineStr.size(); i++ )
    {
        if( lineStr.at(i) == 'R' )
        {
            buttons_Disk[i + 24]->setProperty("current", "true");
            buttons_Disk[i + 24]->setStyleSheet("");

            if ( ui->testWidget->currentIndex() != 1 )
            {
                foreach (QPushButton *b, buttons_Disk)
                {
                    b->setProperty("current", "false");
                    b->setStyleSheet(""); // 刷新按钮的样式
                }
                return;
            }

            sleep(180);
        }
        else
        {
            /* 报错 */
            fault_Cnt += 1;

            /* 将要写入log文件中的字符串 */
            inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));

            /* 将之显示到log TextEdit */
            ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") + tr("磁盘测试失败！"));
        }
    }

    //关闭文件
    file.close();
{
#if 0
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
        fault_Cnt += 1;
    }

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<< "Open failed.";
        return;
    }

    QString content = "R R R R R R R R\n";

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
        fault_Cnt += 1;
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
#endif
}

}


void Widget::toolButton_Pic_clicked()
{
    myThread::circTest_isOk = false;

    /* 切换Tab至Tab3 */
    ui->testWidget->setCurrentIndex(2);
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    emit this->changeTestFlg(PIC_TEST);
}
void Widget::toggle_Picture()
{
    ui->testWidget->setCurrentIndex(2);
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }
    ui->toolButton_pic->setProperty("current", "true");
    ui->toolButton_pic->setStyleSheet("");

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
}


void Widget::toolButton_Net_clicked()
{
    myThread::circTest_isOk = false;

    ui->testWidget->setCurrentIndex(3);
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    ui->net_textEdit1->clear();
    ui->net_textEdit2->clear();
    ui->net_textEdit2_2->clear();
    ui->net_textEdit2_3->clear();
    ui->net_textEdit2_4->clear();
    ui->net_textEdit2_5->clear();
    emit this->changeTestFlg(NET_TEST);
}
void Widget::net_test()
{
    int exitCode;

    ui->testWidget->setCurrentIndex(3);
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }
    ui->toolButton_net->setProperty("current", "true");
    ui->toolButton_net->setStyleSheet("");

    if( strIPList.isEmpty() )
    {
        strIPList << "127.0.0.1";
        ui->netIPlabel->setText("测试网卡");
    }

    //对每个Ip执行ping命令检测其是否在线
    qDebug() << "ping " << endl;

    foreach (QString ipStr, strIPList) {

        if( ipStr.left(1) == "1192" )
        {
            ui->netIPlabel->setText("主板网卡IP: " + ipStr.remove(0, 1));
        }
        else if( ipStr.left(3) == "127" )
        {

        }
        else
        {
            ui->netIPlabel->setText("网卡板IP: "   + ipStr.remove(0, 1));
        }

        #ifdef Q_OS_WIN
            QString strArg = "ping " + ipStr + " -n 1 -i 2";
            exitCode = QProcess::execute(strArg);

    {
    #if 0
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
    #endif
        }
        #else
            //其他平台(Linux或Mac)
            exitCode = QProcess::execute("ping",  QStringList() << "-c 1" << "-t 2" << ipStr);
        #endif

        /* strArg.arg("~~~~"), 可进行修改 */

        if(0 == exitCode)
        {
            sleep(300);
            //it's alive
            ui->net_textEdit1->setText("接收网卡数据：字节=32 时间<1ms TTL=64");

            if( ui->testWidget->currentIndex() == 3 )
            {
                sleep(600);
                ui->net_textEdit2->setText("接收网卡数据：字节=32 时间<1ms TTL=64");
            }
            else
            {
                return;
            }

            if( ui->testWidget->currentIndex() == 3 )
            {
                sleep(600);
                ui->net_textEdit2_2->setText("接收网卡数据：字节=32 时间<1ms TTL=64");
            }
            else
            {
                return;
            }

            if( ui->testWidget->currentIndex() == 3 )
            {
                sleep(600);
                ui->net_textEdit2_3->setText("接收网卡数据：字节=32 时间<1ms TTL=64");
            }
            else
            {
                return;
            }

            if( ui->testWidget->currentIndex() == 3 )
            {
                sleep(600);
                ui->net_textEdit2_4->setText("接收网卡数据：字节=32 时间<1ms TTL=64");
            }
            else
            {
                return;
            }

            if( ui->testWidget->currentIndex() == 3 )
            {
                sleep(600);
                ui->net_textEdit2_5->setText("接收网卡数据：字节=32 时间<1ms TTL=64");
            }
            else
            {
                return;
            }
        }
        else
        {
            ui->net_textEdit1->setText("请求超时");
            sleep(1000);

            fault_Cnt += 1;
            /* 将要写入log文件中的字符串 */
            inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                              + ipStr + tr("网卡测试失败！"));
            /* 将之显示到log TextEdit */
            ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                  + ipStr + tr("网卡测试失败！"));
        }
        sleep(300);

        ui->net_textEdit1->clear();
        ui->net_textEdit2->clear();
        ui->net_textEdit2_2->clear();
        ui->net_textEdit2_3->clear();
        ui->net_textEdit2_4->clear();
        ui->net_textEdit2_5->clear();
    }
}


void Widget::toolButton_Uart_clicked()
{
    myThread::circTest_isOk = false;

    if( infos.isEmpty() )
    {
        QMessageBox::warning(this, "warning Message", "无串口设备");
        ui->testWidget->setCurrentIndex(0);
        emit this->changeTestFlg(55);

        ui->toolButton_ram->setProperty("current", "true");
        ui->toolButton_ram->setStyleSheet("");     // 刷新按钮的样式
        ui->toolButton_uart->setProperty("current", "false");
        ui->toolButton_uart->setStyleSheet("");    // 刷新按钮的样式

        return;
    }

    ui->testWidget->setCurrentIndex(4);
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    emit this->changeTestFlg(UART_TEST);
}
void Widget::uart_test()
{
    QString strText = "abc";
    QByteArray ch = strText.toLatin1();

    ui->testWidget->setCurrentIndex(4);
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }
    ui->toolButton_uart->setProperty("current", "true");
    ui->toolButton_uart->setStyleSheet("");

    foreach ( QSerialPortInfo info, infos )
    {
        ui->textEdit_1->clear();
        ui->textEdit_10->clear();
        ui->textEdit_2->clear();
        ui->textEdit_8->clear();
        ui->textEdit_3->clear();
        ui->textEdit_9->clear();

        sleep(500);

        ui->comboBox->currentIndexChanged( info.portName() );

        if ( ui->testWidget->currentIndex() == 4 )
        {
            if( serial.write(ch) == -1 )
            {
                fault_Cnt += 1;
                ui->textEdit_1->setText("发送数据失败");

                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                  + info.portName() + tr("串口发送数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                      + info.portName() + tr("串口发送数据测试失败！"));
                return;
            }
            else
            {
                ui->textEdit_1->setText("发送数据：" + strText + " 成功");
            }
        }
        else
            return;

        sleep(500);

        if ( ui->testWidget->currentIndex() == 4 )
        {
            QByteArray temp = serial.readAll();

            if( !temp.isEmpty() )
            {
                ui->textEdit_10->setText(tr("接收数据：") + temp + tr("成功"));
            }
            else
            {
                ui->textEdit_10->setText("接收数据失败");

                fault_Cnt += 1;

                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                  + info.portName() + tr("串口接收数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + info.portName() + tr("串口接收数据测试失败！"));
            }
        }
        else
            return;
        sleep(500);

        if ( ui->testWidget->currentIndex() == 4 )
        {
            if( serial.write(ch) == -1 )
            {
                ui->textEdit_2->setText("发送数据失败");

                fault_Cnt += 1;
                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                  + info.portName() + tr("串口发送数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + info.portName() + tr("串口发送数据测试失败！"));
                return;
            }
            else
            {
                ui->textEdit_2->setText("发送数据：" + strText + " 成功");
            }
        }
        else
            return;

        sleep(500);

        if ( ui->testWidget->currentIndex() == 4 )
        {
            QByteArray temp = serial.readAll();

            if( !temp.isEmpty() )
            {
                ui->textEdit_8->setText(tr("接收数据：") + temp + tr("成功"));
            }
            else
            {
                ui->textEdit_8->setText("接收数据失败");

                fault_Cnt += 1;
                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                  + info.portName() + tr("串口接收数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + info.portName() + tr("串口接收数据测试失败！"));
            }
        }
        else
            return;
        sleep(500);

        if ( ui->testWidget->currentIndex() == 4 )
        {
            if( serial.write(ch) == -1 )
            {
                ui->textEdit_3->setText("发送数据失败");

                fault_Cnt += 1;
                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                  + info.portName() + tr("串口发送数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + info.portName() + tr("串口发送数据测试失败！"));
                return;
            }
            else
            {
                ui->textEdit_3->setText("发送数据：" + strText + " 成功");
            }
        }
        else
            return;
        sleep(500);

        if ( ui->testWidget->currentIndex() == 4 )
        {
            QByteArray temp = serial.readAll();

            if( !temp.isEmpty() )
            {
                ui->textEdit_9->setText(tr("接收数据：") + temp + tr("成功"));
            }
            else
            {
                ui->textEdit_9->setText("接收数据失败");

                /* 发生错误,记错 */
                fault_Cnt += 1;
                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                 + info.portName() + tr("串口接收数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + info.portName() + tr("串口接收数据测试失败！"));
            }
        }
        else
            return;
        sleep(500);
    }

    sleep(700);
}


void Widget::toolButton_Mouse_clicked()
{
    myThread::circTest_isOk = false;
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    ui->testWidget->setCurrentIndex(6);

    emit this->changeTestFlg(MOUSE_TEST);
}
void Widget::mouse_test()
{
    /* 实际测试: event进入时间很慢,所以在需要实时得到鼠标坐标的时候并不适用,解决办法就是加快进入事件的次数,例入: */
    QMouseEvent event(QEvent::User, pos, Qt::NoButton, Qt::NoButton, 0);
    QTime t;
    t.start();
    while(t.elapsed() < 8000)
    {
        QApplication::sendEvent(this, &event);
        QCoreApplication::processEvents();
    }
}

void Widget::toolButton_BLANKBD_clicked()
{
    struct hid_device_info *devs;
    myThread::circTest_isOk = false;
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    /* 清除测试界面已有文字 */
    keyCodeClearSlot();
    clearInfoUsbDateSlot();
    ui->pidLineEdit->clear();
    ui->vidLineEdit->clear();

    /* 首先停止其他测试项目 */
    emit this->changeTestFlg(MOUS_TEST);

    if( kbdLite_isOk == true )
    {
        ui->testWidget->setCurrentIndex(5);
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
        ui->testWidget->setCurrentIndex(5);
        emit this->changeTestFlg(BLANK_TEST);
    }
}

void Widget::toolButton_KBD_clicked()
{
    myThread::circTest_isOk = false;
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    ui->testWidget->setCurrentIndex(8);

    /* 停止其他测试 */
    emit this->changeTestFlg(MOUS_TEST);
}

/* 键盘类中循坏测试的处理代码 */
void Widget::circleKBDTest(int signal)
{
    if( signal == 0 )
    {
        ui->testWidget->setCurrentIndex(8);
        foreach (QToolButton *b, buttons)
        {
            b->setProperty("current", "false");
            b->setStyleSheet(""); // 刷新按钮的样式
        }
        ui->toolButton_kbd->setProperty("current", "true");
        ui->toolButton_kbd->setStyleSheet("");

        if( ui->testWidget->currentIndex() == 8 )
        {
            sleep(1000);
        }
        else
            return;
        if( ui->testWidget->currentIndex() == 8 )
        {
            sleep(1000);
        }
        else
            return;
        if( ui->testWidget->currentIndex() == 8 )
        {
            sleep(1000);
        }
        else
            return;
        if( ui->testWidget->currentIndex() == 8 )
        {
            sleep(1000);
        }
        else
            return;
    }
    else if( signal == 1 )
    {    
        if( kbdLite_isOk == true )
        {
            ui->testWidget->setCurrentIndex(5);
            foreach (QToolButton *b, buttons)
            {
                b->setProperty("current", "false");
                b->setStyleSheet(""); // 刷新按钮的样式
            }
            ui->toolButton_kbdlite->setProperty("current", "true");
            ui->toolButton_kbdlite->setStyleSheet("");
        }
    }
    else if( signal == 2 )
    {
        ui->testWidget->setCurrentIndex(6);
        foreach (QToolButton *b, buttons)
        {
            b->setProperty("current", "false");
            b->setStyleSheet(""); // 刷新按钮的样式
        }
        ui->toolButton_mouse->setProperty("current", "true");
        ui->toolButton_mouse->setStyleSheet("");

        /* 实际测试: event进入时间很慢,所以在需要实时得到鼠标坐标的时候并不适用,解决办法就是加快进入事件的次数,例入: */
        mouse_test();
    }
}

void Widget::selectTestItem_clicked()
{
    myThread::circTest_isOk = false;

    foreach (QCheckBox *c, checkBoxs)
    {
        c->show();
        c->setEnabled(true);
        c->setChecked(false);
    }

    if ( kbdLite_isOk == false )
        ui->checkBox7->hide();

    /* 停止循环测试 */
    ui->label_3->setText(tr("请在左侧勾选循环测试的测试项"));
    ui->testWidget->setCurrentIndex(9);
    emit this->changeTestFlg(MOUS_TEST);
}
void Widget::circleButton_clicked()
{
    int i = 0;

    foreach (QCheckBox *c, checkBoxs)
    {
        if( c->isChecked() == true )
            i += 1;
    }
    if( i == 0 )
    {
        QMessageBox::warning(this, "warning Message", "请选择循环测试项或直接进行单项测试");
        ui->selectTestItemBtm->click();
        return;
    }

    myThread::circTest_isOk = true;

    foreach (QCheckBox *c, checkBoxs)
    {
        c->setEnabled(false);
    }

    emit this->changeTestFlg(CIRC_TEST);
}
void Widget::checkBox_stateChanged(int state)
{
    int i = 0;

    foreach (QCheckBox *c, checkBoxs)      /* 当一个CheckBox状态发送改变时遍历所有CheckBox */
    {
        if( c->isChecked() == true )
        {
            myThread::checkBox_TestFlg[i] = true;
        }
        else
        {
            myThread::checkBox_TestFlg[i] = false;
        }
        i++;
    }
}
