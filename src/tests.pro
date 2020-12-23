QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

linux-g++* {
  LIBS += -lcurl
}

win32 {
  # remember to put libcurl-x64 to mingw folder
  LIBS += C:/curl-7.74.0-win64-mingw/lib/libcurl.a \
          C:/curl-7.74.0-win64-mingw/lib/libcurl.dll.a
  INCLUDEPATH += C:/curl-7.74.0-win64-mingw/include
}

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
