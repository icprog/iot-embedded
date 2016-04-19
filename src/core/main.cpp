#include <QCoreApplication>
#include <QMetaObject>
#include <dataitem.h>
#include "ApplicationContextLoader.h"
#include "PluginLoader.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("IoTEmbeddedClient");
    QCoreApplication::setOrganizationName("JMSsolutions");
    QCoreApplication a(argc, argv);
    qRegisterMetaType<DataItem>();

    ApplicationContextLoader context(&a);
    PluginLoader* loader = new PluginLoader(&context);

//    SensorNodeFactory* test = loader->loadPlugin<SensorNodeFactory>("/home/jakub/workspace/cpp/Qt/iot-embedded/build/plugins/system-telemetry-sensor/libsystem_telemetry_sensor.so");

    NodeContainer<SensorNode, SensorNodeFactory>* sensor_container =
            new NodeContainer<SensorNode, SensorNodeFactory>(&context);
    NodeContainer<BrokerNode, BrokerNodeFactory>* broker_container =
            new NodeContainer<BrokerNode, BrokerNodeFactory>(&context);
    NodeContainer<ConnectivityNode, ConnectivityNodeFactory>* connectivity_container =
            new NodeContainer<ConnectivityNode, ConnectivityNodeFactory>(&context);

    context.setSensorContainer(sensor_container);
    context.setBrokerContainer(broker_container);
    context.setConnectivityContainer(connectivity_container);

    context.setPluginLoader(loader);

//    context.loadTestContext();
    context.loadApplicationContext("/home/jakub");
    context.dumpObjectTree();

    return a.exec();

//    return 0;
}
