#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T13:29:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV_test
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    dotpatternbuilder.cpp

HEADERS  += mainwindow.h \
    dotpatternbuilder.h

FORMS    += mainwindow.ui
LIBS += `pkg-config opencv --libs`
