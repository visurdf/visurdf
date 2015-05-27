# -------------------------------------------------
# Project created by QtCreator 2015-05-13T16:13:29
# -------------------------------------------------
QT += core
QT += svg
CONFIG += link_pkgconfig
PKGCONFIG += raptor2

# CONFIG += link_pkgconfig
# PKGCONFIG += raptor2
# LIBS	+= pkg-config raptor2 --cflags --libs
TARGET = VisuRDF
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    visurdfextractor.cpp \
    classesvg.cpp \
    objet.cpp \
    type.cpp \
    generateur.cpp \
    visurdfanalyseur.cpp \
    dessinateur.cpp
HEADERS += visurdfextractor.h \
    classesvg.h \
    objet.h \
    type.h \
    generateur.h \
    visurdfanalyseur.h \
    dessinateur.h
OTHER_FILES += Makefile
