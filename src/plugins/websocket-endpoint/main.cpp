#include <QCoreApplication>
#include <QMetaObject>
#include <QSettings>
#include <WebsocketEndpointFactory.h>

//class test : public QObject {
//    ;.
//};

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("IoTEmbeddedClient");
    QCoreApplication::setOrganizationName("JMSsolutions");
    QCoreApplication a(argc, argv);
    qRegisterMetaType<DataItem>();

    ConnectivityNodeFactory *f = new WebsocketEndpointFactory(&a);
    ConnectivityNode* ws = f->createNode("wsTest");
    ws->start();

    QByteArray tst = "dupa";
    DataItem item;
    item.payload().insert("data",tst);

    ws->sendData(item);

    return a.exec();
}
