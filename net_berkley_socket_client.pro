TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        client.cpp \
        getfilesize.cpp \
        main.cpp \
        nameaddresscontainer.cpp
LIBS += \
       -lboost_system\

HEADERS += \
    client.h \
    getfilesize.h \
    nameaddresscontainer.h

