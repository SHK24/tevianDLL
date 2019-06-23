#-------------------------------------------------
#
# Project created by QtCreator 2019-06-22T22:10:25
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = tevianDLL
TEMPLATE = lib

CONFIG += shared
DEFINES += TEVIANDLL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        detectRequest.cpp \
        loginrequest.cpp \
        request.cpp \
        teviandll.cpp \

HEADERS += \
        detectRequest.h \
        loginrequest.h \
        request.h \
        teviandll.h \
        teviandll_global.h  \

LIBS += "..\build-UsageOfPersonDll-Desktop_Qt_5_2_0_MinGW_32bit-Debug\debug\Person.dll"

unix {
    target.path = /usr/lib
    INSTALLS += target
}