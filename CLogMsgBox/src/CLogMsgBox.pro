CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(clogmsgboxplugin)
TEMPLATE    = lib

HEADERS     = clogmsgboxplugin.h
SOURCES     = clogmsgboxplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(clogmsgbox.pri)
