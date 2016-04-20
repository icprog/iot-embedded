#include <QCoreApplication>
#include <QMetaObject>
#include <QSettings>
#include <WebsocketEndpointFactory.h>
int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("IoTEmbeddedClient");
    QCoreApplication::setOrganizationName("JMSsolutions");
    QCoreApplication a(argc, argv);
    qRegisterMetaType<DataItem>();

    ConnectivityNodeFactory *f = new WebsocketEndpointFactory(&a);
    ConnectivityNode* ws = f->createNode("wsTest");
    ws->start();

    return a.exec();
}
