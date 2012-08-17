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
    phoebetriaapp.cpp \
    bfx-recon/fancontroller.cpp \
    device-io.cpp \
    temperaturemonitor.cpp \
    profiles.cpp \
    fanchanneldata.cpp

HEADERS  += gui_mainwindow.h \
    phoebetriaapp.h \
    bfx-recon/fancontroller.h \
    device-io.h \
    temperaturemonitor.h \
    profiles.h \
    fanchanneldata.h

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

unix:!macx {
    CONFIG += link_pkgconfig
    PKGCONFIG += libusb-1.0
    SOURCES += hidapi-0.7.0/linux/hid-libusb.c
    LIBS += -lusb-1.0 -ludev -lrt
}
macx {
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
    QMAKE_MAC_SDK=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk
    LIBS += -framework CoreFoundation -framework IOKit
    SOURCES += hidapi-0.7.0/mac/hid.c
    ICON = Phoebetria.icns
}

RESOURCES += \
    gui_resources.qrc

OTHER_FILES +=
