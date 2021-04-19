#-------------------------------------------------
#
# Project created by QtCreator 2021-04-18T21:11:21
#
#-------------------------------------------------

QT       += core gui charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fitness
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    weather.cpp \
    calc.cpp \
    MAX30102.cpp

HEADERS  += mainwindow.h \
    weather.h \
    calc.h \
    i2c-dev.h \
    MAX30102.h

FORMS    += mainwindow.ui

DISTFILES += \
    MAX30102.py
INCLUDEPATH += -I/usr/include/python3.5m -I/usr/include/python3.5m
LIBS += -L/usr/lib/python3.5/config-3.5m-arm-linux-gnueabihf -L/usr/lib -lpython3.5m

