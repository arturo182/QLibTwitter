QT         += core network xml
QT         -= gui

TARGET      = QLibTwitter
CONFIG     += console
CONFIG     -= app_bundle
TEMPLATE    = app
INCLUDEPATH = ../src
DEPENDPATH  = ../lib

CONFIG(debug, release|debug) {
  LIBS += -L../lib -lQLibTwitterd
} else {
  LIBS += -L../lib -lQLibTwitter
}

SOURCES    += main.cpp \
              Test.cpp

HEADERS    += Test.h
