#-------------------------------------------------
#
# Project created by QtCreator 2016-10-30T10:35:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpServer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ThreadSocket.cpp

HEADERS  += MainWindow.h \
    ThreadSocket.h

FORMS    += MainWindow.ui
