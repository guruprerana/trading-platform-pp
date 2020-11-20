QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api/api.cpp \
    main.cpp \
    gui/mainwindow.cpp \
    components/portfolio/portfolio.cpp \
    components/security/security.cpp \
    components/trading_order/trading_order.cpp

HEADERS += \
    api/api.h \
    gui/mainwindow.h \
    components/portfolio/portfolio.h \
    components/security/security.h \
    components/trading_order/trading_order.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
