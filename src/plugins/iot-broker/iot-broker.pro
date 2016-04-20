#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T23:17:05
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(iot_broker)
TEMPLATE = lib
CONFIG += plugin c++11

DEFINES += IOTBROKER_LIBRARY

SOURCES += \
    IotBroker.cpp \
    IoTBrokerFactory.cpp \
    JsonMessageFormatter.cpp \
    StompMessageFormatter.cpp

HEADERS += \ 
    IotBroker.h \
    IoTBrokerFactory.h \
    JsonMessageFormatter.h \
    MessageFormattingStrategy.h \
    StompMessageFormatter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../build/sdk/ -liot-embedded-sdk \
                    -lqstomp

INCLUDEPATH += $$PWD/../../sdk \
               $$PWD/../../sdk/interfaces \
               /usr/include/qt5/QStomp/
DEPENDPATH += $$PWD/../../sdk
