#ifndef WEBSOCKETENDPOINTFACTORY_H
#define WEBSOCKETENDPOINTFACTORY_H

#include <QObject>
#include <ConnectivityNodeFactory.h>

class WebsocketEndpointFactory : public QObject, public ConnectivityNodeFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.jmssolutions.iot.embedded.plugin.node.WebsocketEndpoint")
    Q_INTERFACES(ConnectivityNodeFactory)

public:
    explicit WebsocketEndpointFactory(QObject *parent = 0);
    ConnectivityNode *createNode(const QString &node_name) override final;
    QByteArray getNodeClassName() override final;
private:
    const static QString TAG;
};

#endif // WEBSOCKETENDPOINTFACTORY_H
