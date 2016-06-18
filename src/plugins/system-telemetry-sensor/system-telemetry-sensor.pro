#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T23:17:05
#
#-------------------------------------------------

QT       -= gui

TARGET = $$qtLibraryTarget(system_telemetry_sensor)
TEMPLATE = lib
CONFIG += plugin c++11

DEFINES += SYSTEMTELEMETRYSENSOR_LIBRARY

SOURCES += \
    Sensor.cpp \
    SensorWorker.cpp \
    system_telemetry/SystemTelemetrySensorFactory.cpp \
    system_telemetry/SystemTelemetryWorker.cpp \
    system_telemetry/TelemetryDataProvider.cpp

HEADERS += \
    Sensor.h \
    SensorWorker.h \
    system_telemetry/SystemTelemetrySensorFactory.h \
    system_telemetry/SystemTelemetryWorker.h \
    system_telemetry/TelemetryDataProvider.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../build/sdk/ -liot-embedded-sdk

INCLUDEPATH += $$PWD/../../sdk \
               $$PWD/../../sdk/interfaces
DEPENDPATH += $$PWD/../../sdk
