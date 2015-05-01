TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG += debug

LIBS+=-lpthread -lrt `pkg-config --cflags --libs dbus-1`

SOURCES += data-engine.c \
    core.c \
    main.c

HEADERS += \
    data-engine.h \
    core.h

INCLUDEPATH += /usr/include/dbus-1.0
INCLUDEPATH += /usr/lib/i386-linux-gnu/dbus-1.0/include/ 
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/dbus-1.0/include/
QMAKE_CFLAGS_DEBUG += -std=gnu99
