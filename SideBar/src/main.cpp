#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    /* 全屏显示，另外一种全屏显示w.showFullScreen();，效果连标题栏都能去掉 */
//    w.setWindowState(Qt::WindowMaximized);
    w.setMinimumSize(1783, 971);
    w.show();

    return a.exec();
}
