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

    /* 5个勾选框，分别对应于五个测试项 2017-2-5 15:18:51 添加三个测试*/
    {
        checkBoxs.append(ui->checkBox1);
        checkBoxs.append(ui->checkBox2);
        checkBoxs.append(ui->checkBox3);
        checkBoxs.append(ui->checkBox4);
        checkBoxs.append(ui->checkBox5);
        checkBoxs.append(ui->checkBox6);
        checkBoxs.append(ui->checkBox7);
        checkBoxs.append(ui->checkBox8);
    }

    foreach (QCheckBox *c, checkBoxs)
    {
        connect(c, SIGNAL(stateChanged(int)), this, SLOT(checkBox_stateChanged(int)));    /* 连接信号signal */
    }

    ui_RightButtons.append(ui->selectTestItemBtm);
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

