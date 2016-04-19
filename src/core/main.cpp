#include <QCoreApplication>
#include <QMetaObject>
#include <dataitem.h>
#include "ApplicationContextLoader.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("IoTEmbeddedClient");
    QCoreApplication::setOrganizationName("JMSsolutions");
    QCoreApplication a(argc, argv);
    qRegisterMetaType<DataItem>();

    ApplicationContextLoader context(&a);
    NodeContainer* container = new NodeContainer(&context);
    container->getNode<ConnectivityNode>("odbyt");
    context.setNodeContainer(container);


//    context.loadTestContext();
    context.loadApplicationContext("/home/jakub");
    context.dumpObjectTree();

    return a.exec();

//    return 0;
}
