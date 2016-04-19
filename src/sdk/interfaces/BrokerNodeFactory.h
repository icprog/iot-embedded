#ifndef BrokerNODEFACTORY_H
#define BrokerNODEFACTORY_H
#include <BrokerNode.h>

/**
 * @brief The BrokerNodeFactory interface
 * @details This is interface exported to plugin.
 *          Creates instance of plugins.
 */
class BrokerNodeFactory
{
public:
    /**
     * @brief ~BrokerNodeFactory Virtual desctuctor
     */
    virtual ~BrokerNodeFactory() {}

    /**
     * @brief createNode Node instance method
     * @return instance of Node interface
     */
    virtual BrokerNode *createNode(const QString &node_name) = 0;

    virtual QByteArray getNodeClassName() = 0;

};

#include <QObject>
#define BrokerNodeFactory_iid "com.jmssolutions.iot.embedded.plugin.node.BrokerNodeFactory"
Q_DECLARE_INTERFACE(BrokerNodeFactory, BrokerNodeFactory_iid)

#endif // BrokerNODEFACTORY_H
