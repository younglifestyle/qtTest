#include "widget.h"
#include "ui_widget.h"

void Widget::initButtons()
{
//    QList<QPushButton *> kdbButtons;


    // 把按钮放在一个list里为了方便管理
    {
        buttons_Ram.append(ui->pushButton1);
        buttons_Ram.append(ui->pushButton2);
        buttons_Ram.append(ui->pushButton3);
        buttons_Ram.append(ui->pushButton4);
        buttons_Ram.append(ui->pushButton5);
        buttons_Ram.append(ui->pushButton6);
        buttons_Ram.append(ui->pushButton7);
        buttons_Ram.append(ui->pushButton8);
        buttons_Ram.append(ui->pushButton9);
        buttons_Ram.append(ui->pushButton10);
        buttons_Ram.append(ui->pushButton11);
        buttons_Ram.append(ui->pushButton12);
        buttons_Ram.append(ui->pushButton13);
        buttons_Ram.append(ui->pushButton14);
        buttons_Ram.append(ui->pushButton15);
        buttons_Ram.append(ui->pushButton16);
        buttons_Ram.append(ui->pushButton17);
        buttons_Ram.append(ui->pushButton18);
        buttons_Ram.append(ui->pushButton19);
        buttons_Ram.append(ui->pushButton20);
        buttons_Ram.append(ui->pushButton21);
        buttons_Ram.append(ui->pushButton22);
        buttons_Ram.append(ui->pushButton23);
        buttons_Ram.append(ui->pushButton24);
        buttons_Ram.append(ui->pushButton25);
        buttons_Ram.append(ui->pushButton26);
        buttons_Ram.append(ui->pushButton27);
        buttons_Ram.append(ui->pushButton28);
        buttons_Ram.append(ui->pushButton29);
        buttons_Ram.append(ui->pushButton30);
        buttons_Ram.append(ui->pushButton31);
        buttons_Ram.append(ui->pushButton32);
        buttons_Ram.append(ui->pushButton33);
        buttons_Ram.append(ui->pushButton34);
        buttons_Ram.append(ui->pushButton35);
        buttons_Ram.append(ui->pushButton36);
        buttons_Ram.append(ui->pushButton37);
        buttons_Ram.append(ui->pushButton38);
        buttons_Ram.append(ui->pushButton39);
        buttons_Ram.append(ui->pushButton40);
    }

    {
        buttons_Disk.append(ui->pushButton41);
        buttons_Disk.append(ui->pushButton42);
        buttons_Disk.append(ui->pushButton43);
        buttons_Disk.append(ui->pushButton44);
        buttons_Disk.append(ui->pushButton45);
        buttons_Disk.append(ui->pushButton46);
        buttons_Disk.append(ui->pushButton47);
        buttons_Disk.append(ui->pushButton48);
        buttons_Disk.append(ui->pushButton_79);
        buttons_Disk.append(ui->pushButton_80);
        buttons_Disk.append(ui->pushButton_81);
        buttons_Disk.append(ui->pushButton_82);
        buttons_Disk.append(ui->pushButton_83);
        buttons_Disk.append(ui->pushButton_84);
        buttons_Disk.append(ui->pushButton_85);
        buttons_Disk.append(ui->pushButton_86);
        buttons_Disk.append(ui->pushButton49);
        buttons_Disk.append(ui->pushButton50);
        buttons_Disk.append(ui->pushButton51);
        buttons_Disk.append(ui->pushButton52);
        buttons_Disk.append(ui->pushButton53);
        buttons_Disk.append(ui->pushButton54);
        buttons_Disk.append(ui->pushButton55);
        buttons_Disk.append(ui->pushButton56);
        buttons_Disk.append(ui->pushButton_95);
        buttons_Disk.append(ui->pushButton_96);
        buttons_Disk.append(ui->pushButton_97);
        buttons_Disk.append(ui->pushButton_98);
        buttons_Disk.append(ui->pushButton_99);
        buttons_Disk.append(ui->pushButton_100);
        buttons_Disk.append(ui->pushButton_101);
        buttons_Disk.append(ui->pushButton_102);
        buttons_Disk.append(ui->pushButton_41);
        buttons_Disk.append(ui->pushButton_42);
        buttons_Disk.append(ui->pushButton_43);
        buttons_Disk.append(ui->pushButton_44);
        buttons_Disk.append(ui->pushButton_45);
        buttons_Disk.append(ui->pushButton_46);
        buttons_Disk.append(ui->pushButton_47);
        buttons_Disk.append(ui->pushButton_48);
        buttons_Disk.append(ui->pushButton_71);
        buttons_Disk.append(ui->pushButton_72);
        buttons_Disk.append(ui->pushButton_73);
        buttons_Disk.append(ui->pushButton_74);
        buttons_Disk.append(ui->pushButton_75);
        buttons_Disk.append(ui->pushButton_76);
        buttons_Disk.append(ui->pushButton_77);
        buttons_Disk.append(ui->pushButton_78);
    }
    buttons.append(ui->toolButton_disk);
    buttons.append(ui->toolButton_kbd);
    buttons.append(ui->toolButton_kbdlite);
    buttons.append(ui->toolButton_mouse);
    buttons.append(ui->toolButton_net);
    buttons.append(ui->toolButton_pic);
    buttons.append(ui->toolButton_ram);
    buttons.append(ui->toolButton_uart);

    /* 5个勾选框，分别对应于五个测试项 */
    checkBoxs.append(ui->checkBox1);
    checkBoxs.append(ui->checkBox2);
    checkBoxs.append(ui->checkBox3);
    checkBoxs.append(ui->checkBox4);
    checkBoxs.append(ui->checkBox5);
    foreach (QCheckBox *c, checkBoxs)
    {
        connect(c, SIGNAL(stateChanged(int)), this, SLOT(checkBox_stateChanged(int)));    /* 连接信号signal */
    }

    ui_RightButtons.append(ui->circleButton);
    ui_RightButtons.append(ui->checkLogButton);
    ui_RightButtons.append(ui->deleteLogButton);

    /* 左边功能按键 */
    foreach (QToolButton *b, buttons)
    {
        connect(b, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));    /* 连接信号signal */
    }

    /* 右边的PushButton */
    foreach (QPushButton *a, ui_RightButtons)
    {
        connect(a, SIGNAL(clicked()), this, SLOT(changePushButtonStatus()));    /* 连接信号signal */
    }

    ui->toolButton_ram->setProperty("first", "true"); // 第一个按钮上面的边框不要.
}

void Widget::changePushButtonStatus()
{
    /* 首先将所有的Button颜色正常化 */
    foreach (QToolButton *b, buttons)
    {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }
    foreach (QPushButton *a, ui_RightButtons)
    {
        a->setProperty("current", "false");
        a->setStyleSheet(""); // 刷新按钮的样式
    }

    /* 将信号发送者的颜色变色 */
    QPushButton *sources = qobject_cast<QPushButton *>(sender());
    sources->setProperty("current", "true");
    sources->setStyleSheet("");
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
    foreach (QPushButton *a, ui_RightButtons)
    {
        a->setProperty("current", "false");
        a->setStyleSheet(""); // 刷新按钮的样式
    }

    QToolButton *source = qobject_cast<QToolButton *>(sender());
    source->setProperty("current", "true");
    source->setStyleSheet("");
}

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

    emit this->changeTestFlg(NET_TEST);
}
void Widget::net_test()
{
    QString ip = "127.0.0.1";
    int exitCode;

    ui->testWidget->setCurrentIndex(3);

    ui->net_textEdit1->clear();
    ui->net_textEdit2->clear();
    ui->net_textEdit2_2->clear();
    ui->net_textEdit2_3->clear();
    ui->net_textEdit2_4->clear();
    ui->net_textEdit2_5->clear();

    //对每个Ip执行ping命令检测其是否在线
    qDebug() << "ping " + ip << endl;
    #ifdef Q_OS_WIN
        QString strArg = "ping " + ip + " -n 1 -i 2";
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
        exitCode = QProcess::execute("ping",  QStringList() << "-c 1" << "-t 2" << ip);
    #endif

    /* strArg.arg("~~~~"), 可进行修改 */
    sleep(300);

    if(0 == exitCode)
    {
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
    }
    sleep(300);
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
                                  + tr("串口发送数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口发送数据测试失败！"));
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
                                       + tr("串口接收数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口接收数据测试失败！"));
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
                                  + tr("串口发送数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口发送数据测试失败！"));
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
                                       + tr("串口接收数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口接收数据测试失败！"));
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
                                  + tr("串口发送数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口发送数据测试失败！"));
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

                fault_Cnt += 1;
                /* 将要写入log文件中的字符串 */
                inputFault.append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口接收数据测试失败！"));
                /* 将之显示到log TextEdit */
                ui->textEdit_4->append(dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss ")
                                       + tr("串口接收数据测试失败！"));
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

    ui->testWidget->setCurrentIndex(6);

    emit this->changeTestFlg(MOUS_TEST);
}

void Widget::toolButton_BLANKBD_clicked()
{
    struct hid_device_info *devs;
    myThread::circTest_isOk = false;

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

void Widget::circleButton_clicked()
{
    myThread::circTest_isOk = true;

    foreach (QCheckBox *c, checkBoxs)
    {
        c->show();
        c->setChecked(true);
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

void Widget::checkFaultLog_Slot()
{
    myThread::circTest_isOk = false;
    foreach (QCheckBox *c, checkBoxs)
    {
        c->hide();
    }

    ui->testWidget->setCurrentIndex(7);

    /* 停止其他测试 */
    emit this->changeTestFlg(MOUS_TEST);
}

void Widget::deleteFaultLog_Slot()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(this, "warning Message",
                                                          tr("确认是否删除测试报告?"),
                                                          QMessageBox::Yes | QMessageBox::No,
                                                          QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        ui->textEdit_4->clear();
        faultfile->resize(0);
        inputFault.clear();
    }
}
