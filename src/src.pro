TEMPLATE = lib
QT = core widgets network

PROJECT_ROOT = $$PWD/..
include($$PROJECT_ROOT/config/qmakeitup.pri)

INCLUDEPATH += $$PWD

DEFINES += LIBDUBOZERO_LIBRARY
contains(DUBO_LINK_TYPE, static){
    DEFINES += LIBDUBOZERO_USE_STATIC
}

copyToDestdir($$PWD/lib$${TARGET}/*.h, $$DESTDIR/../include/lib$${TARGET})
copyToDestdir($$PWD/../res/redist/*, $$DESTDIR/../share/lib$${TARGET})

SOURCES +=  $$PWD/root.cpp\
            $$PWD/browser.cpp \
            $$PWD/registrar.cpp \
            $$PWD/resolver.cpp \
            $$PWD/genericzero.cpp \
            $$PWD/dubozero.cpp

HEADERS +=  $$PWD/lib$${TARGET}/global.h \
            $$PWD/lib$${TARGET}/root.h \
            $$PWD/lib$${TARGET}/browser.h \
            $$PWD/lib$${TARGET}/record.h \
            $$PWD/lib$${TARGET}/registrar.h \
            $$PWD/lib$${TARGET}/resolver.h \
            $$PWD/lib$${TARGET}/genericzero.h \
            $$PWD/lib$${TARGET}/dubozero.h
