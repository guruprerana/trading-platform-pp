QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lcurl

SOURCES +=  tst_api.cpp \
    tst_stock.cpp \
    ../src/api/api.cpp \
    ../src/components/stock.cpp \
    ../src/components/news.cpp \

HEADERS += \
    ../src/api/api.h \
    ../src/components/stock.h \
    ../src/helper/QJsonObjectManipulation.h \
    ../src/components/news.h \
