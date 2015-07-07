#-------------------------------------------------
#
# Project created by QtCreator 2013-08-30T10:36:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = CSnake
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    world.cpp \
    snake.cpp \
    graphicsengine.cpp

HEADERS += \
    world.h \
    snake.h \
    graphicsengine.h

QMAKE_CXXFLAGS += -std=c++11
