QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    api/api.cpp \
    components/stock.cpp \
    components/portfolio.cpp \
    components/trading_order.cpp \
    gui/chooseportfolio.cpp \
    gui/homepage.cpp \
    gui/signup.cpp \
    gui/mainwindow.cpp \
    gui/neworder.cpp \
    main.cpp

HEADERS += \
    api/api.h \
    components/stock.h \
    components/portfolio.h \
    components/trading_order.h \
    gui/chooseportfolio.h \
    gui/homepage.h \
    gui/signup.h \
    gui/neworder.h \
    gui/mainwindow.h \
    helper/QJsonObjectManipulation.h \
    helper/QEnumManipulation.h
    
FORMS += \
    gui/chooseportfolio.ui \
    gui/homepage.ui \
    gui/mainwindow.ui \
    gui/signup.ui \
    gui/neworder.ui

DISTFILES += \
    style.astylerc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
