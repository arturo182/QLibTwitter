QT         += core
QT         -= gui

TARGET      = TwitOAvis
CONFIG     += console
CONFIG     -= app_bundle
TEMPLATE    = app
INCLUDEPATH = ../src
DEPENDPATH  = ../lib

SOURCES    += main.cpp \
           ../src/TwitOAvis.cpp

HEADERS    w+= ../src/TwitOAvis.h
