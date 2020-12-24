QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lcurl

SOURCES += \
    tests/tst_api.cpp \
    tests/tst_stock.cpp \
    api/api.cpp \
    components/stock.cpp \
    components/news.cpp \
    helper/helper.cpp

HEADERS += \
    api/api.h \
    components/stock.h \
    helper/helper.h \
    components/news.h
