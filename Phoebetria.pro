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

INCLUDEPATH += hidapi-0.7.0/hidapi
SOURCES += hidapi-0.7.0/windows/hid.c
HEADERS += hidapi-0.7.0/hidapi/hidapi.h

LIBS += -lsetupapi
