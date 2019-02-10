#-------------------------------------------------
# Project created by QtCreator 2019-02-09T01:01:01
#-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualizer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    visualizer.cpp \
    widgets/mainwindow.cpp \
    widgets/glwidget.cpp \
    shaders/vizpointcloud.cpp

HEADERS += \
    widgets/mainwindow.hpp \
    widgets/glwidget.hpp \
    shaders/vizpointcloud.hpp

DISTFILES +=
