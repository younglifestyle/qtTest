#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    /* 全屏显示，另外一种全屏显示w.showFullScreen();，效果连标题栏都能去掉 */
    w.setMinimumSize(1180, 670);        /* 设置窗口最小尺寸，在Designer中无法修改尺寸了，用代码强行修改 */
    w.resize(1180, 690);                /* 设置完尺寸后，重新显示窗口的尺寸 */
    w.setWindowState(Qt::WindowMaximized);    /* 全屏显示 */
    w.show();

    return a.exec();
}
