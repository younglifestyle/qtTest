#include "widget.h"
#include "ui_widget.h"

void Widget::getUsbPidVidSlot()
{
    unsigned short VID = devInfo.vendor_id;
    unsigned short PID = devInfo.product_id;

    ui->vidLineEdit->setText("0x0" + QString::number(VID, 16));
    ui->pidLineEdit->setText("0x0" + QString::number(PID, 16));
}

void Widget::receive0x0AData_setText_Slot(unsigned char *keyBuf)
{
    if( keyBuf == Q_NULLPTR )
        return;

    ui->k1LineEdit->setText( "0x" + QString::number(keyBuf[1],16));
    ui->k2LineEdit->setText( "0x" + QString::number(keyBuf[2],16));
    ui->k3LineEdit->setText( "0x" + QString::number(keyBuf[3],16));
    ui->k4LineEdit->setText( "0x" + QString::number(keyBuf[4],16));
    ui->k5LineEdit->setText( "0x" + QString::number(keyBuf[5],16));
    ui->k6LineEdit->setText( "0x" + QString::number(keyBuf[6],16));
    ui->k7LineEdit->setText( "0x" + QString::number(keyBuf[7],16));

    ui->k8LineEdit->setText( "0x" + QString::number(keyBuf[8], 16));
    ui->k9LineEdit->setText( "0x" + QString::number(keyBuf[9], 16));
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
        QMessageBox::warning(this, "warning Message", "USB设备未插入或被占用，通信出错");
        kbdLite_isOk = false;
        ui->testWidget->setCurrentIndex(9);        /* 跳转到介绍页面 */
        emit this->changeTestFlg(55);              /* 停止测试 */
        ui->toolButton_kbdlite->setProperty("current", "false");   /* 取消高亮 */
        ui->toolButton_kbdlite->setStyleSheet(""); // 刷新按钮的样式
        return;
    }
    else
    {
       if(KeyBuf[1] == 0x00)
       {
           ui->k1PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K01 Down: 0x" + QString::number(KeyBuf[1],16) );
       }
       if(KeyBuf[1] == 0x80)
       {
            ui->k1PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K01   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x01)
       {
           ui->k2PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K02 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x81)
       {
            ui->k2PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K02   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x02)
       {
           ui->k3PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K03 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x82)
       {
            ui->k3PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K03   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x03)
       {
           ui->k4PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K04 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x83)
       {
            ui->k4PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K04   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x04)
       {
           ui->k5PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K05 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x84)
       {
            ui->k5PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K05   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x05)
       {
           ui->k6PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K06 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x85)
       {
            ui->k6PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K06   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x06)
       {
           ui->k7PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K07 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x86)
       {
            ui->k7PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K07   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x07)
       {
           ui->k8PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K08 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x87)
       {
            ui->k8PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K08   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x08)
       {
           ui->k9PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K09 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x88)
       {
            ui->k9PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K09   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x09)
       {
           ui->k10PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K10 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x89)
       {
            ui->k10PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K10   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x0A)
       {
           ui->k11PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K16 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x8A)
       {
            ui->k11PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K11   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x0B)
       {
           ui->k12PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K12 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x8B)
       {
            ui->k12PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K12   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x0C)
       {
           ui->k13PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K13 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x8C)
       {
            ui->k13PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K13   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x0D)
       {
           ui->k14PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K14 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x8D)
       {
            ui->k14PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K14   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x0E)
       {
           ui->k15PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K15 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x8E)
       {
            ui->k15PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K15   Up: 0x" + QString::number(KeyBuf[1],16));
       }

       if(KeyBuf[1] == 0x0F)
       {
           ui->k16PushButton->setStyleSheet("background-color:rgb(0, 255, 0)");
           ui->keyTextEdit->append("K16 Down: 0x" + QString::number(KeyBuf[1],16));
       }
       if(KeyBuf[1] == 0x8F)
       {
            ui->k16PushButton->setStyleSheet("");
            ui->keyTextEdit->append("K16   Up: 0x" + QString::number(KeyBuf[1],16));
       }
//        ui->keyTextEdit->append("0x" + QString::number(KeyBuf[1], 16));
    }
}
