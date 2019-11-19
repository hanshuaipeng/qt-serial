#-------------------------------------------------
#
# Project created by QtCreator 2019-11-11T09:31:05
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = comtest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
