#-------------------------------------------------
#
# Project created by QtCreator 2012-08-02T07:50:29
#
#-------------------------------------------------

QT       += core gui

TARGET = Phoebetria
TEMPLATE = app

PREFIX = /usr
BINDIR = $$PREFIX/bin
DATADIR = $$PREFIX/share
ICONDIR = $$DATADIR/icons/hicolor

INSTALLS += target desktop udev icon16 icon22 icon32 icon48 icon64 icon128 icon256 pixmap

target.path = $${BINDIR}

desktop.path = $${DATADIR}/applications
desktop.files += $${TARGET}.desktop

udev.path = /etc/udev/rules.d
udev.files += 99-fancontroller.rules

icon16.path = $${ICONDIR}/16x16/apps
icon16.files += Images/icons/16x16/phoebetria.png

icon22.path = $${ICONDIR}/22x22/apps
icon22.files += Images/icons/22x22/phoebetria.png

icon32.path = $${ICONDIR}/32x32/apps
icon32.files += Images/icons/32x32/phoebetria.png

icon48.path = $${ICONDIR}/48x48/apps
icon48.files += Images/icons/48x48/phoebetria.png

icon64.path = $${ICONDIR}/64x64/apps
icon64.files += Images/icons/64x64/phoebetria.png

icon128.path = $${ICONDIR}/128x128/apps
icon128.files += Images/icons/128x128/phoebetria.png

icon256.path = $${ICONDIR}/256x256/apps
icon256.files += Images/icons/256x256/phoebetria.png

pixmap.path = $${DATADIR}/pixmaps
pixmap.files += Images/icons/48x48/phoebetria.png


SOURCES += main.cpp\
        gui_mainwindow.cpp \
    phoebetriaapp.cpp \
    bfx-recon/fancontroller.cpp \
    device-io.cpp \
    profiles.cpp \
    fanchanneldata.cpp \
    fancontrollerdata.cpp \
    gui_about.cpp \
    builddetails.cpp \
    bfx-recon/fancontrollerio.cpp \
    utils.cpp

HEADERS  += gui_mainwindow.h \
    phoebetriaapp.h \
    bfx-recon/fancontroller.h \
    device-io.h \
    profiles.h \
    fanchanneldata.h \
    fancontrollerdata.h \
    gui_about.h \
    builddetails.h \
    bfx-recon/fancontrollerio.h \
    utils.h

FORMS    += gui_mainwindow.ui \
    gui_about.ui

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
