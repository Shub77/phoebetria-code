#-------------------------------------------------
#
# Project created by QtCreator 2012-08-02T07:50:29
#
#-------------------------------------------------

QT       += core gui

TARGET = Phoebetria
TEMPLATE = app

SOURCES += main.cpp\
        gui_mainwindow.cpp \
    phoebetriaapp.cpp

HEADERS  += gui_mainwindow.h \
    phoebetriaapp.h

FORMS    += gui_mainwindow.ui

#-------------------------------------------------
# Config for the HID API library
#-------------------------------------------------

INCLUDEPATH += hidapi-0.7.0/hidapi
HEADERS += hidapi-0.7.0/hidapi/hidapi.h
win32 {
    SOURCES += hidapi-0.7.0/windows/hid.c
    LIBS += -lsetupapi
}
<<<<<<< HEAD
linux-g++ {
=======
unix {
>>>>>>> 50e3a083e30e4e6a8347648bc1986b0ba5bd46db
    CONFIG += link_pkgconfig
    PKGCONFIG += libusb-1.0
    SOURCES += hidapi-0.7.0/linux/hid-libusb.c
    LIBS += -lusb-1.0 -ludev -lrt
}
