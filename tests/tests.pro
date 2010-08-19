QT         += core network xml
QT         -= gui

TARGET      = QLibTwitter
CONFIG     += console
CONFIG     -= app_bundle
TEMPLATE    = app
INCLUDEPATH = ../src
DEPENDPATH  = ../lib

SOURCES    += main.cpp \
              Test.cpp \
              ../src/QLibTwitterCore.cpp \
              ../src/QLibOA/src/QLibOAUtil.cpp \
              ../src/QLibOA/src/QLibOAToken.cpp \
              ../src/QLibOA/src/QLibOASignatureHMAC.cpp \
              ../src/QLibOA/src/QLibOARequest.cpp \
              ../src/QLibOA/src/QLibOAConsumer.cpp \
              ../src/QLibTwitterParser.cpp

HEADERS    += Test.h \
              ../src/QLibTwitterCore.h \
              ../src/QLibOA/src/QLibOAUtil.h \
              ../src/QLibOA/src/QLibOAToken.h \
              ../src/QLibOA/src/QLibOASignaturePlainText.h \
              ../src/QLibOA/src/QLibOASignatureHMAC.h \
              ../src/QLibOA/src/QLibOASignature.h \
              ../src/QLibOA/src/QLibOARequest.h \
              ../src/QLibOA/src/QLibOAConsumer.h \
              ../src/QLibOA/src/QLibOACommon.h \
              ../src/QLibTwitterCommon.h \
              ../src/QLibTwitterParser.h
