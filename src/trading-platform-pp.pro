QT       += core gui printsupport

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
    gui/signup.cpp \
    gui/stockdashboard.cpp \
    gui/stockgraph.cpp \
    gui/stockgraphonemonth.cpp \
    gui/stockgraphsixmonths.cpp \
    gui/stockgraphthreedays.cpp \
    main.cpp \
    gui/mainwindow.cpp \
    library/qcustomplot.cpp \
    components/portfolio/portfolio.cpp \
    components/trading_order/trading_order.cpp

HEADERS += \
    api/api.h \
    components/stock.h \
    gui/mainwindow.h \
    gui/chooseportfolio.h \
    gui/homepage.h \
    gui/signup.h \
    gui/stockdashboard.h \
    gui/stockgraph.h \
    gui/stockgraphonemonth.h \
    gui/stockgraphsixmonths.h \
    gui/stockgraphthreedays.h \
    helper/QJsonObjectManipulation.h \
    library/qcustomplot.h \
    components/portfolio/portfolio.h \
    components/trading_order/trading_order.h
    
FORMS += \
    gui/chooseportfolio.ui \
    gui/homepage.ui \
    gui/mainwindow.ui \
    gui/signup.ui \
    gui/stockdashboard.ui \
    gui/stockgraph.ui

DISTFILES += \
    style.astylerc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
