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
    interfacecoreview.cpp \
    constantnode.cpp \
    stdoutnode.cpp \
    dataport.cpp \
    inputdataport.cpp \
    outputdataport.cpp \
    datavalue.cpp \
    mergernode.cpp \
    additionnode.cpp \
    splitternode.cpp

HEADERS  += \
    oglwidget.h \
    processnode.h \
    interfacecoreapp.h \
    interfacecoreview.h \
    constantnode.h \
    stdoutnode.h \
    dataport.h \
    inputdataport.h \
    outputdataport.h \
    datavalue.h \
    mergernode.h \
    additionnode.h \
    splitternode.h

FORMS    +=
