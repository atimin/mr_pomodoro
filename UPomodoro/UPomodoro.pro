#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T16:44:35
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_upomodoro
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_upomodoro.cpp ../pomodoro.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../pomodoro.h
