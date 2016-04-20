#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T23:17:05
#
#-------------------------------------------------

QT       -= gui
QT       += network
QT       += websockets
TARGET = $$qtLibraryTarget(websocket-endpoint)
TEMPLATE = lib
CONFIG += plugin c++11

DEFINES += WEBSOCKETENDPOINT_LIBRARY

SOURCES += \
    socket/SocketEndpoint.cpp \
    WebsocketEndpointFactory.cpp


HEADERS += \
    socket/Socket.h \
    socket/SocketEndpoint.h \
    WebsocketEndpointFactory.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../build/sdk/ -liot-embedded-sdk

INCLUDEPATH += $$PWD/../../sdk \
               $$PWD/../../sdk/interfaces
DEPENDPATH += $$PWD/../../sdk
