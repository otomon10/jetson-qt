#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T22:28:14
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = example-app-01
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    led.cpp \
    switch.cpp \
    gpio.cpp

HEADERS += \
        mainwindow.h \
    led.h \
    gpio.h \
    switch.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/nvidia/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    memo
