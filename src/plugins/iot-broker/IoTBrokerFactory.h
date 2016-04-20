#ifndef IOTBROKERFACTORY_H
#define IOTBROKERFACTORY_H

#include <BrokerNodeFactory.h>
class IoTBrokerFactory :public QObject, public BrokerNodeFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.jmssolutions.iot.embedded.plugin.node.IoTBroker")
    Q_INTERFACES(BrokerNodeFactory)
public:

    explicit IoTBrokerFactory(QObject* parent = 0);
    virtual BrokerNode *createNode(const QString &node_name) override final;

    virtual QByteArray getNodeClassName() override final;
private:
    const static QString TAG;
};

#include <QObject>
#define IoTBrokerFactory_iid "com.jmssolutions.iot.embedded.plugin.node.IoTBrokerFactory"
Q_DECLARE_INTERFACE(IoTBrokerFactory, IoTBrokerFactory_iid)

#endif // IOTBROKERFACTORY_H
