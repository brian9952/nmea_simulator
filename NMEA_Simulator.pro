QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    nmeadata.cpp \
    mainwindow.cpp \
    serialportdialog.cpp \
    startupdialog.cpp \
    aamdialog.cpp \
    boddialog.cpp \
    libs/RangeSlider.cpp

HEADERS += \
    nmeadata.h \
    mainwindow.h \
    serialportdialog.h \
    startupdialog.h \
    aamdialog.h \
    boddialog.h \
    libs/RangeSlider.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
