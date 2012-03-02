#-------------------------------------------------
#
# Project created by QtCreator 2011-07-08T18:00:46
#
#-------------------------------------------------

QT       += testlib xml script

TARGET = tst_usagetest
CONFIG   += console qtestlib
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    Test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

# external library linking options
DEPENDPATH += . /home/maluen/Scrivania/programmazione/pwf-framework/pwf/engine/src
INCLUDEPATH += /home/maluen/Scrivania/programmazione/pwf-framework/pwf/engine/src
LIBS += -L/home/maluen/Scrivania/programmazione/pwf-framework/pwf/engine/bin -lpwfengine

HEADERS += \
    Test.h
