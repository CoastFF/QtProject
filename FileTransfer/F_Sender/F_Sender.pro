#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T14:32:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = F_Sender
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    clsTransaction.cpp \
    clsThread.cpp

HEADERS  += MainWindow.h \
    clsTransaction.h \
    clsThread.h

FORMS    += MainWindow.ui
