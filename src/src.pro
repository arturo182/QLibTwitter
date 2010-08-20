TARGET = QLibTwitter
TEMPLATE = lib
DESTDIR = ../lib

QT += network xml

HEADERS += QLibTwitterCommon.h \
           QLibTwitterParser.h \
           QLibTwitterCore.h \
           QLibTwitterCommon.h \
           QLibOA/src/QLibOAUtil.h \
           QLibOA/src/QLibOAToken.h \
           QLibOA/src/QLibOASignaturePlainText.h \
           QLibOA/src/QLibOASignatureHMAC.h \
           QLibOA/src/QLibOASignature.h \
           QLibOA/src/QLibOARequest.h \
           QLibOA/src/QLibOAConsumer.h \
           QLibOA/src/QLibOACommon.h


SOURCES += QLibTwitterParser.cpp \
           QLibTwitterCore.cpp \
           QLibOA/src/QLibOAUtil.cpp \
           QLibOA/src/QLibOAToken.cpp \
           QLibOA/src/QLibOASignatureHMAC.cpp \
           QLibOA/src/QLibOARequest.cpp \
           QLibOA/src/QLibOAConsumer.cpp

CONFIG(debug_and_release) {
    build_pass:CONFIG(debug, debug|release) {
        TARGET = $$join(TARGET,,,d)
    }
}
