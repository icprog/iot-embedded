#include <QCoreApplication>
#include <QMetaObject>
#include <QSettings>
#include <IotBroker.h>
#include <IoTBrokerFactory.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("IoTEmbeddedClient");
    QCoreApplication::setOrganizationName("JMSsolutions");
    QCoreApplication a(argc, argv);
    qRegisterMetaType<DataItem>();

    BrokerNodeFactory *f = new IoTBrokerFactory(&a);
    BrokerNode* broker = f->createNode("IoTBroker1");
    broker->start();

    return a.exec();

//    return 0;
}
