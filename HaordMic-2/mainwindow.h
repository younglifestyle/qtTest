#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hidapi.h"
#include <QDebug>
#include <windows.h>
#include <QMessageBox>
#include <QTime>
#include <QPushButton>
#include <QCloseEvent>
#include "thread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sleep(unsigned int msec);

private:
    Ui::MainWindow *ui;

protected:
    void closeEvent(QCloseEvent *e);
private:
    Thread threadA;

private slots:
    void getUsbDeviceSlot();
    void sendUsbDateSlot();
//    void clearUsbDateSlot();
    void clearrecUsbDateSlot();

    void keyClearSlot();

    void startOrStopThreadA();
    void quitSlot();
    void keyOutDateSlot(unsigned char *pq);
};

#endif // MAINWINDOW_H
