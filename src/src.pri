QT = core

TARGET = qtsignal
TEMPLATE = lib

DEFINES += QXTSIGNAL_LIBRARY

SOURCES += \
    $$PWD/qxtsignalwaiter.cpp \
    $$PWD/qxtsignalgroup.cpp \
    $$PWD/qxtmultisignalwaiter.cpp

HEADERS += \
    $$PWD/qxtsignal_global.h \
    $$PWD/qxtsignalwaiter.h\
    $$PWD/qxtsignalgroup.h \
    $$PWD/qxtmultisignalwaiter.h
