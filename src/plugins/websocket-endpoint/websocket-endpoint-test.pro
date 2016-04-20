#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T23:17:05
#
#-------------------------------------------------

QT       -= gui
QT       += network core websockets

TARGET = websocket-endpoint-test
TEMPLATE = app
CONFIG += c++11 console

DEFINES += WEBSOCKETENDPOINT_LIBRARY

SOURCES += main.cpp \
    socket/SocketEndpoint.cpp \
    WebsocketEndpointFactory.cpp \
    QWebSocketWrapper.cpp


HEADERS += \
    socket/Socket.h \
    socket/SocketEndpoint.h \
    WebsocketEndpointFactory.h \
    QWebSocketWrapper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../build/sdk/ -liot-embedded-sdk

INCLUDEPATH += $$PWD/../../sdk \
               $$PWD/../../sdk/interfaces
DEPENDPATH += $$PWD/../../sdk
