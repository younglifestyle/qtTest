#include "widget.h"
#include "ui_widget.h"

void Widget::changeLabelTime(const QString &Tim)
{
    ui->timeCnt->setText(Tim);
}

void Widget::changeLabelfault(const QString &date)
{
    ui->errorCnt->setText(date);
}

void Widget::changeLableCircleDate(const QString &date)
{
    ui->circleCnt->setText(date);
}

/* 读取配置文件中的网卡信息 */
void Widget::readCfgText()
{
    QString lineStr;

    if ( !cfgfile->exists() )
    {
        return;
    }

    if ( cfgfile->size() != 0 )
    {
        bool ok = cfgfile->open( QIODevice::ReadOnly );

        qDebug() << "+++";
        if ( ok )
        {
            int i = 0;
            QTextStream in(cfgfile);
            while ( !in.atEnd() )
            {
                lineStr = in.readLine();

                if( lineStr.left(3) == "192" )
                {
                    if( i == 1 )
                    {
                        strIPList << "1" + lineStr;
                    }
                    else if( i == 2 )
                    {
                        strIPList << "2" + lineStr;
                    }
                }
                else
                {
                    i += 1;
                }
            }

            cfgfile->close();
        }
    }
    else
    {
//        qDebug() << "213";
    }
}

void Widget::setfaultLogTextEdit()
{
    QString lineStr;

    /* 错误记录 */
    ui->textEdit_4->setStyleSheet("background-color:transparent;");

    ui->textEdit_4->setFontPointSize(20);
    ui->textEdit_4->setTextColor(QColor("white"));

//    qDebug() << faultfile->exists();

    /* 不存在即创建 */
    if ( !faultfile->exists() )
    {
        faultfile->open( QIODevice::WriteOnly );
        faultfile->close();
    }

    if ( faultfile->size() != 0 )
    {
        bool ok = faultfile->open( QIODevice::ReadWrite );

        qDebug() << ok;

        if ( ok )
        {
            QTextStream in(faultfile);
            while ( !in.atEnd() )
            {
                lineStr = in.readLine();
                if ( lineStr.left(10) == dateTime.currentDateTime().toString("yyyy-MM-dd") )
                {
                    ui->textEdit_4->append( lineStr );
                }
            }

            faultfile->close();
        }
    }
}

/* 查看错误报告 */
void Widget::checkFaultLog_Slot()
{
    myThread::circTest_isOk = false;
    foreach (QCheckBox *c, checkBoxs)
    {
        if( ! c->isHidden() )
            c->hide();
    }

    ui->testWidget->setCurrentIndex(7);

    /* 全选按键若没有隐藏，则隐藏 */
    if ( !ui->allSelectButtom->isHidden() )
        ui->allSelectButtom->hide();

    /* 停止其他测试 */
    emit this->changeTestFlg(MOUS_TEST);
}

void Widget::deleteFaultLog_Slot()
{
    /* 全选按键若没有隐藏，则隐藏 */
    if ( !ui->allSelectButtom->isHidden() )
        ui->allSelectButtom->hide();

    foreach (QCheckBox *c, checkBoxs)
    {
        if( ! c->isHidden() )
            c->hide();
    }

    QMessageBox::StandardButton rb = QMessageBox::warning(this, "warning Message",
                                                          tr("确认是否删除测试报告?"),
                                                          QMessageBox::Yes | QMessageBox::No,
                                                          QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        ui->textEdit_4->clear();

        fault_Cnt = 0;
        faultfile->resize(0);
        inputFault.clear();
    }
}
