QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lcurl

SOURCES +=  tst_api.cpp \
    ../../src/api/api.cpp

HEADERS += \
    ../../src/api/api.h
