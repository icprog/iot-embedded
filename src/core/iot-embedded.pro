QT += core
QT -= gui

CONFIG += c++11

TARGET = iot-embedded
CONFIG += console
QT += network
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    NodeContainer.cpp \
    ApplicationContextLoader.cpp \
    PluginLoader.cpp

    #plugin/iot-broker/QStomp/qstomp.cpp

HEADERS += \
    NodeContainer.h \
    ApplicationContextLoader.h \
#    interfaces/SensorNodeFactory.h \
#    interfaces/BrokerNodeFactory.h \
#    interfaces/ConnectivityNodeFactory.h \
    PluginLoader.h


QMAKE_CXXFLAGS_WARN_OFF += -Wunused-parameter

unix:!macx: LIBS += -L$$PWD/../../build/sdk/ -liot-embedded-sdk

INCLUDEPATH += $$PWD/../sdk \
               $$PWD/../sdk/interfaces
DEPENDPATH += $$PWD/../sdk
