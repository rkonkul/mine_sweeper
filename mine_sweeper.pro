#-------------------------------------------------
#
# Project created by QtCreator 2011-10-27T11:58:49
#
#-------------------------------------------------

QT       += core gui static

TARGET = mine_sweeper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Button.cpp

HEADERS  += mainwindow.h \
    Button.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    scores.txt \
    names.txt

RESOURCES +=

CONFIG += -static

QMAKE_LFLAGS += -static








