#ifndef WEBSOCKETENDPOINTFACTORY_H
#define WEBSOCKETENDPOINTFACTORY_H

#include <QObject>
#include <ConnectivityNodeFactory.h>

/**
 * @brief The WebsocketEndpointFactory class
 * @details Produces SocketEndpoint instances specialized to use with WebSocket
 */
class WebsocketEndpointFactory : public QObject, public ConnectivityNodeFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.jmssolutions.iot.embedded.plugin.node.WebsocketEndpoint")
    Q_INTERFACES(ConnectivityNodeFactory)

public:
    /**
     * @brief WebsocketEndpointFactory Constructor
     * @param parent Factory parent.
     */
    explicit WebsocketEndpointFactory(QObject *parent = 0);

    /**
     * @brief createNode Creates instance of node with given name
     * @param node_name Node name
     * @return Pointer to node instance
     */
    ConnectivityNode *createNode(const QString &node_name) override final;

    /**
     * @brief getNodeClassName Return node class name ("WebSocketEndpoint")
     */
    QByteArray getNodeClassName() override final;
private:
    const static QString TAG;
};

#endif // WEBSOCKETENDPOINTFACTORY_H
