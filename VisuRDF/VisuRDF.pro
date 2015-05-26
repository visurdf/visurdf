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
    visurdfextractor.cpp \
    visurdfanalyseur.cpp \
    type.cpp \
    objet.cpp \
    main.cpp \
    generateur.cpp \
    dessinateur.cpp \
    classesvg.cpp
HEADERS += visurdfextractor.h \
    classesvg.h \
    objet.h \
    type.h \
    generateur.h \
    visurdfextractor.h \
    visurdfanalyseur.h \
    type.h \
    objet.h \
    generateur.h \
    dessinateur.h \
    classesvg.h
OTHER_FILES += visurdfextractor.o \
    visurdfanalyseur.o \
    VisuRDF.pro.user.279e1fc.18 \
    VisuRDF.pro.user.28c7db0.3.3-pre1 \
    VisuRDF.pro.user.2.6pre1 \
    VisuRDF.pro.user \
    type.o \
    testSVG.svg \
    PTR-2.rdf \
    props.txt \
    objet.o \
    Makefile
