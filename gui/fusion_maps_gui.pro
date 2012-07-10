#-------------------------------------------------
#
# Project created by QtCreator 2012-06-14T15:53:41
#
#-------------------------------------------------

QT       += core gui

TARGET = fusion_maps_gui
TEMPLATE = app

LIBS+= -lqwt
LIBS+= `pkg-config --cflags --libs dbus-1`

SOURCES += main.cpp\
        fusionmapsgui.cpp \
    data-engine.cpp

HEADERS  += fusionmapsgui.h \
    data-engine.h \
    plot-engine.h

FORMS    += fusionmapsgui.ui

INCLUDEPATH += /usr/include/qwt
INCLUDEPATH += /usr/include/dbus-1.0
INCLUDEPATH += /usr/lib/i386-linux-gnu/dbus-1.0/include/

CONFIG += qwt debug
