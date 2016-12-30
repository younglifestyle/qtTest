#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T08:55:51
#
#-------------------------------------------------

RC_ICONS = 1-2.ico

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HaordMicro_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    hidapi.h \
    thread.h

LIBS += $$quote(E:\QT_works\HaordMicro_2\hidapi.lib)

FORMS    += mainwindow.ui
