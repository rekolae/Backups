TEMPLATE = app
CONFIG += console c++14 warn_on
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ruutu.cpp 

HEADERS += \
    ruutu.hh

QMAKE_CXXFLAGS += -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
