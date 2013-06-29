#-------------------------------------------------
#
# Project created by QtCreator 2013-01-08T20:26:30
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Interface
TEMPLATE = app

LIBS += -lGLU

SOURCES += main.cpp\
    oglwidget.cpp \
    processnode.cpp \
    interfacecoreapp.cpp \
    interfacecoreview.cpp

HEADERS  += \
    oglwidget.h \
    processnode.h \
    interfacecoreapp.h \
    interfacecoreview.h

FORMS    +=
