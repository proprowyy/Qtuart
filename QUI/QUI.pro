#-------------------------------------------------
#
# Project created by QtCreator 2014-08-15T14:34:50
#
#-------------------------------------------------

QT       += core gui

QT += widgets

TARGET = QUI
TEMPLATE = app
QT       += serialport

SOURCES += main.cpp\
        frmmain.cpp \
    iconhelper.cpp \
    frmmessagebox.cpp

HEADERS  += frmmain.h \
    iconhelper.h \
    frmmessagebox.h \
    myhelper.h

FORMS    += frmmain.ui \
    frmmessagebox.ui

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj
DESTDIR=bin

win32:RC_FILE=main.rc

RESOURCES += \
    rc.qrc
