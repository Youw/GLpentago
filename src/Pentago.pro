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
    GLinterface/label.cpp \
    GLinterface/GLfontutils.cpp \
    GLinterface/menu.cpp \
    GLinterface/textedit.cpp


HEADERS  += glview.h \
    GLinterface/textures.h \
    GLinterface/renderobject.h \
    GLinterface/button.h \
    GLinterface/label.h \
    GLinterface/GLfontutils.h \
    GLinterface/menu.h \
    GLinterface/fontkeeper.h \
    GLinterface/fontkeeperbase.h \
    GLinterface/textedit.h \
    GLinterface/GLRectangleCoord.h

RESOURCES += \
    GLinterface/GLgraphics.qrc

CONFIG += c++11

OTHER_FILES += \
    android/AndroidManifest.xml

android {
 DEFINES += HAVE_GLES=true
 LIBS += -lGLESv1_CM
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
