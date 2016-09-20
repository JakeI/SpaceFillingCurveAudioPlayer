#-------------------------------------------------
#
# Project created by QtCreator 2016-07-11T16:21:09
#
#-------------------------------------------------

QT       += core
QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioPlayer
TEMPLATE = app


SOURCES += main.cpp\
    glwindow.cpp \
    texturewindow.cpp \
    glhelper.cpp \
    audiogenerator.cpp \
    audiodivice.cpp \
    hemoltoncurve.cpp

HEADERS  += \
    glwindow.h \
    texturewindow.h \
    glhelper.h \
    audiogenerator.h \
    audiodivice.h \
    hemoltoncurve.h

FORMS    +=

DISTFILES += \
    img.vertex \
    img.fragment
