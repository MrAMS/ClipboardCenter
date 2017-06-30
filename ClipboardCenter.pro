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
    item.cpp \
    MyGlobalShortCut/MyGlobalShortCut.cpp \
    MyGlobalShortCut/MyWinEventFilter.cpp

HEADERS  += clipboarder.h \
    item.h \
    MyGlobalShortCut/MyGlobalShortCut.h \
    MyGlobalShortCut/MyWinEventFilter.h

FORMS    += clipboarder.ui

RESOURCES += \
    icon.qrc

RC_FILE = \
    icon_logo.qrc
