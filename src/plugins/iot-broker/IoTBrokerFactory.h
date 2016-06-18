#ifndef IOTBROKERFACTORY_H
#define IOTBROKERFACTORY_H

#include <BrokerNodeFactory.h>
/**
 * @brief The IoTBrokerFactory class
 * @details Produces IoTBrokerNode instances
 */
class IoTBrokerFactory :public QObject, public BrokerNodeFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.jmssolutions.iot.embedded.plugin.node.IoTBroker")
    Q_INTERFACES(BrokerNodeFactory)
public:

    /**
     * @brief IoTBrokerFactory Constructor
     */
    explicit IoTBrokerFactory(QObject* parent = 0);

    /**
     * @brief createNode Creates node and fulfills it dependencies
     * @param node_name Name of node to be created
     * @return Pointer to node instance
     */
    virtual BrokerNode *createNode(const QString &node_name) override final;

    /**
     * @brief getNodeClassName Returns node class name ("IoTBrokerNode")
     */
    virtual QByteArray getNodeClassName() override final;
private:
    const static QString TAG;
};

#include <QObject>
#define IoTBrokerFactory_iid "com.jmssolutions.iot.embedded.plugin.node.IoTBrokerFactory"
Q_DECLARE_INTERFACE(IoTBrokerFactory, IoTBrokerFactory_iid)

#endif // IOTBROKERFACTORY_H
