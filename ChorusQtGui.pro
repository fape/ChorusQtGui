#-------------------------------------------------
#
# Project created by QtCreator 2017-09-02T19:03:52
#
#-------------------------------------------------

QT       += core gui serialport texttospeech

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChorusQtGui
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


SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
    src/chorusdevice.cpp \
    src/choruslaptimer.cpp \
    src/chorusdeviceform.cpp \
    src/speechinfoholder.cpp \
    src/responseparserv2.cpp \
    src/responseparserfactory.cpp \
    src/responseparser.cpp \
    src/responseparserv4.cpp \
    src/responseparserdefault.cpp

HEADERS += \
        src/mainwindow.h \
    src/chorusdevice.h \
    src/choruslaptimer.h \
    src/chorusdeviceform.h \
    src/speechinfoholder.h \
    src/responseparser.h \
    src/responseparserv2.h \
    src/responseparserfactory.h \
    src/responseparserv4.h \
    src/responseparserdefault.h

FORMS += \
        src/mainwindow.ui \
    src/chorusdeviceform.ui

RESOURCES += \
    resources/chorusqtgui.qrc
