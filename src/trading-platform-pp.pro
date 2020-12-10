QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lcurl

SOURCES += \
    api/api.cpp \
    components/stock.cpp \
    gui/chooseportfolio.cpp \
    gui/homepage.cpp \
    gui/leftnavigationbar.cpp \
    gui/signup.cpp \
    gui/widgets/selectwatchlistwidget.cpp \
    main.cpp \
    gui/mainwindow.cpp \
    components/portfolio/portfolio.cpp \
    components/trading_order/trading_order.cpp \

HEADERS += \
    api/api.h \
    components/stock.h \
    gui/chooseportfolio.h \
    gui/homepage.h \
    gui/leftnavigationbar.h \
    gui/mainwindow.h \
    gui/signup.h \
    gui/widgets/selectwatchlistwidget.h \
    helper/QJsonObjectManipulation.h \
    components/portfolio/portfolio.h \
    components/trading_order/trading_order.h
    
FORMS += \
    gui/chooseportfolio.ui \
    gui/homepage.ui \
    gui/leftnavigationbar.ui \
    gui/mainwindow.ui \
    gui/signup.ui \
    gui/widgets/selectwatchlistwidget.ui

DISTFILES += \
    style.astylerc

RESOURCES += \
    application.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
