#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T16:41:46
#
#-------------------------------------------------

QT       -= gui

TARGET = qxtsignal
TEMPLATE = lib

DEFINES += QXTSIGNAL_LIBRARY

SOURCES += qxtsignalwaiter.cpp \
    qxtsignalgroup.cpp \
    qxtmultisignalwaiter.cpp

HEADERS += qxtsignalwaiter.h\
    qxtsignalgroup.h \
    qxtsignal_global.h \
    qxtmultisignalwaiter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
