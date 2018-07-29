#-------------------------------------------------
#
# Project created by QtCreator 2018-07-26T01:04:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTApktool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    Command.cpp \
    AboutMe.cpp

HEADERS  += mainwindow.h \
    console.h \
    Command.h \
    AboutMe.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
