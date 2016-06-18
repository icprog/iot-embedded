#ifndef SENSORNODEFACTORY_H
#define SENSORNODEFACTORY_H
#include <SensorNode.h>

/**
 * @brief The SensorNodeFactory interface
 * @details This is interface exported to plugin.
 *          Creates instance of plugins.
 */
class SensorNodeFactory
{
public:
    /**
     * @brief ~SensorNodeFactory Virtual desctuctor
     */
    virtual ~SensorNodeFactory() {}

    /**
     * @brief createNode Node instance method
     * @return instance of Node interface
     */
    virtual SensorNode *createNode(const QString &node_name) = 0;

    virtual QByteArray getNodeClassName() = 0;

};

#include <QObject>
#define SensorNodeFactory_iid "com.jmssolutions.iot.embedded.plugin.node.SensorNodeFactory"
Q_DECLARE_INTERFACE(SensorNodeFactory, SensorNodeFactory_iid)

#endif // SENSORNODEFACTORY_H
