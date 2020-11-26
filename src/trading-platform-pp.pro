QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api/api.cpp \
    gui/chooseuser.cpp \
    gui/homepage.cpp \
    gui/leftnavigationbar.cpp \
    gui/signup.cpp \
    main.cpp \
    gui/mainwindow.cpp # \
#    style.astylerc

HEADERS += \
    api/api.h \
    gui/chooseuser.h \
    gui/homepage.h \
    gui/leftnavigationbar.h \
    gui/mainwindow.h \
    gui/signup.h

FORMS += \
    gui/chooseuser.ui \
    gui/homepage.ui \
    gui/leftnavigationbar.ui \
    gui/mainwindow.ui \
    gui/signup.ui

DISTFILES += \
    style.astylerc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
