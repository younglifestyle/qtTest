#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T15:05:30
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HoardMicroTest
TEMPLATE = app

DESTDIR = bin
CONFIG -= app_bundle
UI_DIR = temp
MOC_DIR = temp
OBJECTS_DIR = temp

SOURCES += main.cpp \
    widget.cpp \
    workthread.cpp \
    glwidget.cpp \
    window.cpp

HEADERS  += \
    widget.h \
    workthread.h \
    common.h \
    glwidget.h \
    window.h \
    hidapi.h

FORMS    += \
    widget.ui

LIBS += $$quote(F:\GitWork\SideBar\src\hidapi.lib)

RESOURCES += \
    resources.qrc
