#-------------------------------------------------
#
# Project created by QtCreator 2019-03-14T09:56:28
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Inventory
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cc \
        MainWindow.cc \
    Game.cc \
    Shop.cc \
    ShopRow.cc \
    ItemOld.cc \
    ShopCell.cc \
    Db.cc \
    ItemBase.cc \
    CellBase.cc \
    CellInventar.cc \
    Inventory1.cc \
    Apple1.cc \
    Banana1.cc \
    Ananas1.cc

HEADERS += \
        MainWindow.h \
    config.h \
    Game.h \
    Shop.h \
    ShopRow.h \
    ItemOld.h \
    ShopCell.h \
    Db.h \
    ItemBase.h \
    CellBase.h \
    CellInventar.h \
    Inventory1.h \
    Apple1.h \
    Banana1.h \
    Ananas1.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    items.qrc
