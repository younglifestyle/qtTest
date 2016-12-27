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

signals:
    void changeTestFlg(int);

private slots:
    void changeButtonStatus();
    void toolButton_Ram_clicked();
    void toolButton_Disk_clicked();
    void toolButton_Pic_clicked();
    void toolButton_Net_clicked();
    void toolButton_Uart_clicked();

    void exitButton();

    void toggle_Picture();
    void ram_test();
    void disk_test();
    void net_test();
    void uart_test();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Widget *ui;
    QList<QToolButton *> buttons;

    QImage *image;
    myThread *thread;
    int *ram;
    Window *window;
    QString get_localmachine_ip();

    void initButtons();

};

#endif // SIDEBARDEMO_H
