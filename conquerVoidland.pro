#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T09:16:07
#
#-------------------------------------------------

QT  += core \
    gui \
    opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conquerVoidland
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    monitorwidget.cpp \
    map.cpp \
    robot.cpp \
    explorerrobot.cpp \
    ninjarobot.cpp \
    terminatorrobot.cpp \
    predatorrobot.cpp \
    knowledge.cpp \
    statuswidget.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    monitorwidget.h \
    base.h \
    map.h \
    robot.h \
    explorerrobot.h \
    ninjarobot.h \
    terminatorrobot.h \
    predatorrobot.h \
    knowledge.h \
    robots.h \
    statuswidget.h \
    game.h

INCLUDEPATH += $$PWD
OBJECTS_DIR=$$PWD
DESTDIR=$$PWD
