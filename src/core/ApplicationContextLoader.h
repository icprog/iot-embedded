#ifndef APPLICATIONCONTEXTLOADER_H
#define APPLICATIONCONTEXTLOADER_H

#include <QObject>
#include <QSettings>
#include <memory>
#include "NodeContainer.h"
#include "PluginLoader.h"

class ApplicationContextLoader : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationContextLoader(QObject *parent = 0);

    void loadApplicationContext(const QString &config_path);
    void loadTestContext();

    void setPluginLoader(PluginLoader *plugin_loader);

    void setSensorContainer(NodeContainer<SensorNode, SensorNodeFactory> *sensor_container);
    void setBrokerContainer(NodeContainer<BrokerNode, BrokerNodeFactory> *broker_container);
    void setConnectivityContainer(NodeContainer<ConnectivityNode, ConnectivityNodeFactory> *connectivity_container);

signals:

public slots:

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
};

#endif // APPLICATIONCONTEXTLOADER_H
