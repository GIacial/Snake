#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T15:04:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boule.cpp \
    interfacejeux.cpp \
    serpent.cpp \
    partieserpent.cpp \
    teteserpent.cpp \
    pomme.cpp \
    graphicsbouton.cpp \
    menujeu.cpp

HEADERS  += mainwindow.h \
    boule.h \
    interfacejeux.h \
    serpent.h \
    partieserpent.h \
    teteserpent.h \
    pomme.h \
    graphicsbouton.h \
    menujeu.h

RC_FILE += icone.rc

DISTFILES += \
    icone.rc

