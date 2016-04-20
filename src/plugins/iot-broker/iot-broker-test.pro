QT += core
QT -= gui

CONFIG += c++11

TARGET = iot-embedded-test
CONFIG += console
QT += network
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
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


QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter

unix:!macx: LIBS += -L$$PWD/../../../build/sdk/ -liot-embedded-sdk \
                    -lqstomp


INCLUDEPATH += $$PWD/../../sdk \
               $$PWD/../../sdk/interfaces \
               /usr/include/qt5/QStomp/
DEPENDPATH += $$PWD/../../sdk

