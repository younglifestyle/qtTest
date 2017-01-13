#ifndef SIDEBARDEMO_H
#define SIDEBARDEMO_H

#include <QWidget>
#include <QList>
#include <QMessageBox>
#include <QTextBlock>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QSurfaceFormat>
#include <QPalette>
#include <QDebug>
#include <QColorDialog>
#include <QProcess>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include "hidapi.h"

#include "workthread.h"
#include "window.h"

class QToolButton;

namespace Ui{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void sleep(unsigned int msec);
    void initSeialPort();
    void check_DeviceExist();
    void setfaultLogTextEdit();
    void resizeEvent(QResizeEvent *event);

    QList<QSerialPortInfo> infos;   // 保存计算机上所有的串口信息
    QSerialPort serial;             // 串口实例
    QTimer *timer;
    QTime *time;
    QDateTime dateTime;

    struct hid_device_info devInfo;

    bool circTest_isOk;
    bool kbdLite_isOk;

signals:
    void changeTestFlg(int);
    void changeTimeDate(const QString &Tim);
    void changefaultDate(const QString &date);
    void changeCircleDate(const QString &date);

public slots:
    void onTimeout();

private slots:
    void changeButtonStatus();
    void changePushButtonStatus();

    void toolButton_Ram_clicked();
    void toolButton_Disk_clicked();
    void toolButton_Pic_clicked();
    void toolButton_Net_clicked();
    void toolButton_Uart_clicked();
    void toolButton_Mouse_clicked();
    void toolButton_BLANKBD_clicked();
    void toolButton_KBD_clicked();
    void circleButton_clicked();
    void checkFaultLog_Slot();
    void deleteFaultLog_Slot();

    void getUsbPidVidSlot();
    void receive0x0AData_setText_Slot(unsigned char *keyBuf);
    void clearInfoUsbDateSlot();
    void keyCodeClearSlot();

    void sendUsbCommand_0x0AFlg_Slot();

    void changeLabelTime(const QString &Tim);
    void changeLabelfault(const QString &date);
    void changeLableCircleDate(const QString &date);

    void toggle_Picture();
    void ram_test();
    void disk_test();
    void net_test();
    void uart_test();

    void query_SetKeyTextSlot(unsigned char *KeyBuf);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void checkBox_stateChanged(int state);

protected:
    //鼠标拖动事件
    void mouseMoveEvent(QMouseEvent *e);
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *);
    //按键按下事件
    void keyPressEvent(QKeyEvent *k);

    void keyReleaseEvent(QKeyEvent *e);

    bool event(QEvent *event);

private:
    enum { RAM_CNT = 40, DISK_CNT = 48 };
    enum { RAM = 0x01, DISK = 0x02, PIC = 0x04, NET = 0x08, UART = 0x10 };
    enum {DONT_GO = 0, GO};

    Ui::Widget *ui;
    QList<QToolButton *> buttons;
    QList<QPushButton *> buttons_Ram;
    QList<QPushButton *> buttons_Disk;
    QList<QPushButton *> ui_RightButtons;
    QList<QCheckBox *>   checkBoxs;
    QStringList inputFault;

    QFile *faultfile;
    int fault_Cnt;

    QImage *image;
    QPixmap *pixmap;
    myThread *thread;
    int *ram;
    Window *window;
    QString get_localmachine_ip();

    void initButtons();

};

#endif // SIDEBARDEMO_H
