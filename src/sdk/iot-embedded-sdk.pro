#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T23:19:15
#
#-------------------------------------------------

QT       -= gui

TARGET = iot-embedded-sdk
TEMPLATE = lib

DEFINES += IOT_EMBEDDED_LIBRARY

SOURCES +=  \
        dataitem.cpp


HEADERS += \
        dataitem.h \
        dataitem_global.h \
        interfaces/SensorNode.h \
        interfaces/SensorNodeFactory.h \
        interfaces/BrokerNode.h \
        interfaces/BrokerNodeFactory.h \
        interfaces/ConnectivityNode.h \
        interfaces/ConnectivityNodeFactory.h \
        dataitem_global.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}
