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
    QSerialPort serial;//串口实例
    QTimer *timer;
    QTime *time;
    QDateTime dateTime;

signals:
    void changeTestFlg(int);
    void changeTimeDate(const QString &Tim);
    void changeFalutDate(const QString &date);

public slots:
    void onTimeout();

private slots:
    void changeButtonStatus();

    void toolButton_Ram_clicked();
    void toolButton_Disk_clicked();
    void toolButton_Pic_clicked();
    void toolButton_Net_clicked();
    void toolButton_Uart_clicked();
    void toolButton_Mouse_clicked();
    void getUsbPidVidSlot();
//    void sendUsbCommand_0x0A_Slot();
//    void clearInfoUsbDateSlot();
//    void keyCodeClearSlot();

    void changeLabelTime(const QString &Tim);
    void changeLabelFalut(const QString &date);

    void exitButton();

    void toggle_Picture();
    void ram_test();
    void disk_test();
    void net_test();
    void uart_test();

    void on_comboBox_currentIndexChanged(const QString &arg1);

protected:
    //鼠标拖动事件
    void mouseMoveEvent(QMouseEvent *e);
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::Widget *ui;
    QList<QToolButton *> buttons;

    int falut_Cnt;
    QImage *image;
    myThread *thread;
    int *ram;
    Window *window;
    QString get_localmachine_ip();

    void initButtons();

};

#endif // SIDEBARDEMO_H
