# -------------------------------------------------
# Project created by QtCreator 2015-05-13T16:13:29
# -------------------------------------------------
QT += core
QT += svg
QT += xml
CONFIG += link_pkgconfig
PKGCONFIG += raptor2

# CONFIG += link_pkgconfig
# PKGCONFIG += raptor2
# LIBS	+= pkg-config raptor2 --cflags --libs
TARGET = VisuRDF
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += \
    visurdfanalyseur.cpp \
    visurdfextracteur.cpp \
    visurdftype.cpp \
    visurdfobjet.cpp \
    visurdfmain.cpp \
    visurdfgenerateur.cpp \
    visurdfdessinateur.cpp \
    visurdfboite.cpp\
    visurdfparametreur.cpp \
    mainwindow.cpp \
    visurdfwidget.cpp
HEADERS += \
    visurdfanalyseur.h \
    visurdfextracteur.h \
    visurdftype.h \
    visurdfobjet.h \
    visurdfgenerateur.h \
    visurdfdessinateur.h \
    visurdfboite.h\
    visurdfparametreur.h \
    mainwindow.h \
    visurdfwidget.h
OTHER_FILES += Makefile

FORMS += \
    mainwindow.ui \
    visurdfwidget.ui

RESOURCES += \
    images.qrc
