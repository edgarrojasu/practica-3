TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        escritura.cpp \
        lectura.cpp \
        lz78.cpp \
        main.cpp \
        rle.cpp \
        rotacionbits.cpp \
        xor.cpp

HEADERS += \
    escritura.h \
    lectura.h \
    lz78.h \
    rle.h \
    rotacionbits.h \
    xor.h

DISTFILES += \
    archivoprueba.txt
