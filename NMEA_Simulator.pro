QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    src/nmeadata.cpp \
    src/mainwindow.cpp \
    src/Dialogs/dptdialog.cpp \
    src/Dialogs/hdtdialog.cpp \
    src/Dialogs/mwvdialog.cpp \
    src/Dialogs/rotdialog.cpp \
    src/Dialogs/rsadialog.cpp \
    src/Dialogs/aamdialog.cpp \
    src/Dialogs/boddialog.cpp \
    src/Dialogs/serialportdialog.cpp \
    libs/RangeSlider/RangeSlider.cpp \
    src/threads.cpp \
    src/Dialogs/startupdialog.cpp \

HEADERS += \
    include/datastructs.h \
    include/nmeadata.h \
    include/mainwindow.h \
    include/Dialogs/dptdialog.h \
    include/Dialogs/hdtdialog.h \
    include/Dialogs/mwvdialog.h \
    include/Dialogs/rotdialog.h \
    include/Dialogs/rsadialog.h \
    include/Dialogs/aamdialog.h \
    include/Dialogs/boddialog.h \
    include/Dialogs/serialportdialog.h \
    libs/RangeSlider/RangeSlider.h \
    include/threads.h \
    include/Dialogs/startupdialog.h \

DESTDIR = release
OBJECTS_DIR = release/.obj
MOC_DIR = release/.moc
RCC_DIR = release/.rcc
UI_DIR = release/.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/local/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/cancel_icon.png
