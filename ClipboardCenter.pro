#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T12:49:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClipboardCenter
TEMPLATE = app


SOURCES += main.cpp\
        clipboarder.cpp \
    item.cpp

HEADERS  += clipboarder.h \
    item.h

FORMS    += clipboarder.ui

RESOURCES += \
    icon.qrc
