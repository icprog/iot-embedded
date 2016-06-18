#ifndef ConnectivityNODEFACTORY_H
#define ConnectivityNODEFACTORY_H
#include <ConnectivityNode.h>

/**
 * @brief The ConnectivityNodeFactory interface
 * @details This is interface exported to plugin.
 *          Creates instance of plugins.
 */
class ConnectivityNodeFactory
{
public:
    /**
     * @brief ~ConnectivityNodeFactory Virtual desctuctor
     */
    virtual ~ConnectivityNodeFactory() {}

    /**
     * @brief createNode Node instance method
     * @return instance of Node interface
     */
    virtual ConnectivityNode *createNode(const QString &node_name) = 0;

    virtual QByteArray getNodeClassName() = 0;

};

#include <QObject>
#define ConnectivityNodeFactory_iid "com.jmssolutions.iot.embedded.plugin.node.ConnectivityNodeFactory"
Q_DECLARE_INTERFACE(ConnectivityNodeFactory, ConnectivityNodeFactory_iid)

#endif // ConnectivityNODEFACTORY_H
