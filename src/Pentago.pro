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
    GLinterface/textures.cpp \
    GLinterface/button.cpp \
    GLinterface/label.cpp


HEADERS  += glview.h \
    GLinterface/textures.h \
    GLinterface/renderobject.h \
    GLinterface/button.h \
    GLinterface/label.h

RESOURCES += \
    GLinterface/GLgraphics.qrc

CONFIG += c++11
