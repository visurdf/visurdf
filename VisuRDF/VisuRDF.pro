#-------------------------------------------------
#
# Project created by QtCreator 2015-05-13T16:13:29
#
#-------------------------------------------------

QT       += core
QT       += svg

CONFIG += link_pkgconfig
<<<<<<< HEAD
=======

>>>>>>> 4b6ce32780d26f42926b23b57375d5a1102f357e
PKGCONFIG +=  raptor2


#CONFIG += link_pkgconfig
#PKGCONFIG += raptor2
#LIBS	+= pkg-config raptor2 --cflags --libs

TARGET = VisuRDF
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    visurdfextractor.cpp \
    classesvg.cpp \
    analyseur.cpp \
    objet.cpp \
    type.cpp

HEADERS += \
    visurdfextractor.h \
    classesvg.h \
    analyseur.h \
    objet.h \
    type.h
