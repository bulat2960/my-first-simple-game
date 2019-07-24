#-------------------------------------------------
#
# Project created by QtCreator 2019-06-24T00:50:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyFirstSimpleGame
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
        gui/scene.cpp \
        gui/view.cpp \
        gui/window.cpp \
        logic/battleexecutor.cpp \
        logic/collisiondetector.cpp \
        main.cpp \
        maze/builder.cpp \
        maze/cell.cpp \
        maze/maze.cpp \
        maze/sector.cpp \
        objects/bonus.cpp \
        objects/bot.cpp \
        objects/character.cpp \
        objects/object.cpp \
        objects/player.cpp \
        objects/portal.cpp

HEADERS += \
    globaloptions.h \
    gui/scene.h \
    gui/view.h \
    gui/window.h \
    logic/battleexecutor.h \
    logic/collisiondetector.h \
    maze/builder.h \
    maze/cell.h \
    maze/maze.h \
    maze/sector.h \
    objects/bonus.h \
    objects/bot.h \
    objects/character.h \
    objects/object.h \
    objects/player.h \
    objects/portal.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Static build
# QMAKE_LFLAGS += -static -static-libgcc
# QMAKE_CFLAGS_RELEASE -= O2
# DEFINES += UNICODE QT_STATIC_BUILD
