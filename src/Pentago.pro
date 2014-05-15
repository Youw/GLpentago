#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T17:19:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pentago
TEMPLATE = app


SOURCES += main.cpp\
        glview.cpp \


HEADERS  += glview.h

RESOURCES += \
    GLinterface/GLgraphics.qrc
