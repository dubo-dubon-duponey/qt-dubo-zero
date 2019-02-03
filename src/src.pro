TEMPLATE = lib
QT = core widgets network

PROJECT_ROOT = $$PWD/..
include($$PROJECT_ROOT/config/qmakeitup.pri)

INCLUDEPATH += $$PWD

HEADERS +=  $$PWD/lib$${TARGET}/global.h \
            $$PWD/lib$${TARGET}/root.h \
            $$PWD/lib$${TARGET}/browser.h \
            $$PWD/lib$${TARGET}/record.h \
            $$PWD/lib$${TARGET}/registrar.h \
            $$PWD/lib$${TARGET}/resolver.h \
            $$PWD/lib$${TARGET}/genericzero.h \
            $$PWD/lib$${TARGET}/dubozero.h

SOURCES +=  $$PWD/root.cpp\
            $$PWD/browser.cpp \
            $$PWD/registrar.cpp \
            $$PWD/resolver.cpp \
            $$PWD/genericzero.cpp \
            $$PWD/dubozero.cpp

win32{
# XXX because zero does not abstract bonjour correctly... and this is really shitty
    copyToDestdir($$PWD/../third-party/bonjour-win/include/*.h, $$DESTDIR/../include)
}
