QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lcurl

SOURCES += \
    api/api.cpp \
    components/news.cpp \
    components/session.cpp \
    components/stock.cpp \
    components/portfolio.cpp \
    components/trading_order.cpp \
    gui/chooseportfolio.cpp \
    gui/companynewscard.cpp \
    gui/homepage.cpp \
    gui/newscard.cpp \
    gui/newspage.cpp \
    gui/nodatapage.cpp \
    gui/signalcard.cpp \
    gui/signup.cpp \
    gui/stockgraph.cpp \
    gui/stockgraphoneday.cpp \
    gui/stockgraphonemonth.cpp \
    gui/stockgraphsixmonths.cpp \
    gui/stockgraphthreedays.cpp \
    gui/strategygraph.cpp \
    gui/strategypage.cpp \
    gui/watchlistcard.cpp \
    gui/widgets/watchlistsummarycard.cpp \
    gui/widgets/portfoliowidget.cpp \
    gui/widgets/stockperformancerow.cpp \
    main.cpp \
    gui/mainwindow.cpp \
    recommendation/strategy.cpp \
    library/qcustomplot.cpp \
    helper/helper.cpp \
    gui/widgets/selectwatchlistwidget.cpp \
    gui/neworder.cpp

HEADERS += \
    api/api.h \
    components/news.h \
    components/session.h \
    components/stock.h \
    components/portfolio.h \
    components/trading_order.h \
    gui/chooseportfolio.h \
    gui/companynewscard.h \
    gui/homepage.h \
    gui/newscard.h \
    gui/newspage.h \
    gui/nodatapage.h \
    gui/signalcard.h \
    gui/signup.h \
    gui/stockgraph.h \
    gui/stockgraphoneday.h \
    gui/stockgraphonemonth.h \
    gui/stockgraphsixmonths.h \
    gui/stockgraphthreedays.h \
    gui/strategygraph.h \
    gui/strategypage.h \
    gui/watchlistcard.h \
    gui/widgets/watchlistsummarycard.h \
    gui/widgets/portfoliowidget.h \
    gui/widgets/stockperformancerow.h \
    library/qcustomplot.h \
    gui/neworder.h \
    gui/mainwindow.h \
    gui/widgets/selectwatchlistwidget.h \
    helper/helper.h \
    recommendation/strategy.h
    
FORMS += \
    gui/chooseportfolio.ui \
    gui/companynewscard.ui \
    gui/homepage.ui \
    gui/mainwindow.ui \
    gui/nodatapage.ui \
    gui/signalcard.ui \
    gui/signup.ui \
    gui/stockgraph.ui \
    gui/newscard.ui \
    gui/newspage.ui \
    gui/neworder.ui \
    gui/strategypage.ui \
    gui/watchlistcard.ui \
    gui/widgets/selectwatchlistwidget.ui \
    gui/widgets/watchlistsummarycard.ui \
    gui/widgets/portfoliowidget.ui \
    gui/widgets/stockperformancerow.ui

DISTFILES += \
    style.astylerc

RESOURCES += \
    resources/resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
