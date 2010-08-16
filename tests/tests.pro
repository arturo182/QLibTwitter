QT         += core network xml
QT         -= gui

TARGET      = TwitOAvis
CONFIG     += console
CONFIG     -= app_bundle
TEMPLATE    = app
INCLUDEPATH = ../src
DEPENDPATH  = ../lib

SOURCES    += main.cpp \
              Test.cpp \
              ../src/TwitOAvisCore.cpp \
              ../src/OAvis/OAvisUtil.cpp \
              ../src/OAvis/OAvisToken.cpp \
              ../src/OAvis/OAvisSignatureHMAC.cpp \
              ../src/OAvis/OAvisRequest.cpp \
              ../src/OAvis/OAvisConsumer.cpp \
              ../src/TwitOAvisParser.cpp

HEADERS    += Test.h \
              ../src/TwitOAvisCore.h \
              ../src/OAvis/OAvisUtil.h \
              ../src/OAvis/OAvisToken.h \
              ../src/OAvis/OAvisSignaturePlainText.h \
              ../src/OAvis/OAvisSignatureHMAC.h \
              ../src/OAvis/OAvisSignature.h \
              ../src/OAvis/OAvisRequest.h \
              ../src/OAvis/OAvisConsumer.h \
              ../src/OAvis/OAvisCommon.h \
              ../src/TwitOAvisCommon.h \
              ../src/TwitOAvisParser.h
