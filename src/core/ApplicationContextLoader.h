#ifndef APPLICATIONCONTEXTLOADER_H
#define APPLICATIONCONTEXTLOADER_H

#include <QObject>
#include <QSettings>
#include <memory>
#include "NodeContainer.h"
#include "PluginLoader.h"

/**
 * @brief The ApplicationContextLoader class
 * @details Loads application context from given settins file, then creates nodes and connect them.
 */
class ApplicationContextLoader : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief ApplicationContextLoader Constructor
     * @param parent Context parent. This will be the grand-parent of all nodes.
     */
    explicit ApplicationContextLoader(QObject *parent = 0);

    /**
     * @brief loadApplicationContext Loads application context from settings file.
     * @note Settings file is expected to have QSettings syntax.
     * @note Settings are copied to application settings file where they are accesible for all nodes.
     * @param config_path Path to settings file
     */
    void loadApplicationContext(const QString &config_path);

    /**
     * @brief loadTestContext Test function. Loads hard-coded nodes
     */
    void loadTestContext();

    /**
     * @brief setPluginLoader Sets PluginLoader
     */
    void setPluginLoader(PluginLoader *plugin_loader);

    /**
     * @brief setSensorContainer Sets Sensor Node Container
     */
    void setSensorContainer(NodeContainer<SensorNode, SensorNodeFactory> *sensor_container);

    /**
     * @brief setBrokerContainer Sets Broker Node Container
     */
    void setBrokerContainer(NodeContainer<BrokerNode, BrokerNodeFactory> *broker_container);

    /**
     * @brief setConnectivityContainer Sets Connectivity Node Container
     */
    void setConnectivityContainer(NodeContainer<ConnectivityNode, ConnectivityNodeFactory> *connectivity_container);

private:
    NodeContainer<SensorNode, SensorNodeFactory> *sensor_container_;
    NodeContainer<BrokerNode, BrokerNodeFactory> *broker_container_;
    NodeContainer<ConnectivityNode, ConnectivityNodeFactory> *connectivity_container_;

    PluginLoader *plugin_loader_;
    QSettings *node_settings_;
    QSettings *pipe_settings_;

    void assertNodeContainerExists();
    void loadPlugin();

    const static QString TAG;

    const static QString NODE_SETTINGS_FILENAME;
    const static QString PIPE_SETTINGS_FILENAME;

    const static QString NODE_LIB_FILENAME_KEY;
    const static QString NODE_CLASSNAME_KEY;
    const static QString NODE_CONNECTIONS_KEY;
    const static QString NODE_TYPE_KEY;

signals:
    void startNodes();
};

#endif // APPLICATIONCONTEXTLOADER_H
