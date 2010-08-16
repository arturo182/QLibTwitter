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
              ../src/QLibOA/QLibOAUtil.cpp \
              ../src/QLibOA/QLibOAToken.cpp \
              ../src/QLibOA/QLibOASignatureHMAC.cpp \
              ../src/QLibOA/QLibOARequest.cpp \
              ../src/QLibOA/QLibOAConsumer.cpp \
              ../src/QLibTwitterParser.cpp

HEADERS    += Test.h \
              ../src/QLibTwitterCore.h \
              ../src/QLibOA/QLibOAUtil.h \
              ../src/QLibOA/QLibOAToken.h \
              ../src/QLibOA/QLibOASignaturePlainText.h \
              ../src/QLibOA/QLibOASignatureHMAC.h \
              ../src/QLibOA/QLibOASignature.h \
              ../src/QLibOA/QLibOARequest.h \
              ../src/QLibOA/QLibOAConsumer.h \
              ../src/QLibOA/QLibOACommon.h \
              ../src/QLibTwitterCommon.h \
              ../src/QLibTwitterParser.h
