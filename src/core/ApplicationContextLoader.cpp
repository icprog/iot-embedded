#include "ApplicationContextLoader.h"
#include <QDebug>
#include <stdexcept>
#include <SensorNode.h>
#include <SensorNodeFactory.h>
#include <ConnectivityNode.h>
#include <ConnectivityNodeFactory.h>
#include <BrokerNode.h>
#include <BrokerNodeFactory.h>

const QString ApplicationContextLoader::TAG = "ApplicationContextLoader";
const QString ApplicationContextLoader::NODE_SETTINGS_FILENAME = "nodes.config";
const QString ApplicationContextLoader::PIPE_SETTINGS_FILENAME = "pipelines.config";
const QString ApplicationContextLoader::NODE_LIB_FILENAME_KEY = "filename";
const QString ApplicationContextLoader::NODE_CLASSNAME_KEY = "classname";
const QString ApplicationContextLoader::NODE_CONNECTIONS_KEY = "outboundTo";
const QString ApplicationContextLoader::NODE_TYPE_KEY = "type";

ApplicationContextLoader::ApplicationContextLoader(QObject *parent) : QObject(parent),
                                                                      sensor_container_(nullptr),
                                                                      broker_container_(nullptr),
                                                                      connectivity_container_(nullptr)
{


}

void ApplicationContextLoader::loadApplicationContext(const QString &config_path)
{
     qDebug()<<TAG<<": loadApplicationContext()";
    assertNodeContainerExists();
    /// Try loading settings
    node_settings_ = new QSettings(config_path+"/"+NODE_SETTINGS_FILENAME, QSettings::NativeFormat, this);
    pipe_settings_ = new QSettings(config_path+"/"+PIPE_SETTINGS_FILENAME, QSettings::NativeFormat, this);
    QSettings global_settings;
    qDebug()<<TAG<<": Node settings path: "<<node_settings_->fileName();
    qDebug()<<TAG<<": Pipe settings path: "<<pipe_settings_->fileName();
    qDebug()<<TAG<<": Global settings path: "<<global_settings.fileName();

    /// Load list of node names
    QStringList node_name_list = node_settings_->childGroups();
    if(node_name_list.empty()){
        qDebug()<<TAG<<": node configuration file contains no valid node descriptions.";
        throw new std::runtime_error("nodes.config contains no node description");
    }

    // Lambda alert! Used because I can.
    /// Lambda to copy settings to global settings scope
    auto copySettingsToGlobal = [this, &global_settings](const QString &node_name)->void {
        global_settings.beginGroup(node_name);
        node_settings_->beginGroup(node_name);
        global_settings.remove(""); /**< Removes all settings in group */
        QStringList keys = node_settings_->allKeys();
        foreach (const QString &key, keys) {
            global_settings.setValue(key, node_settings_->value(key));
        }
        global_settings.endGroup();
        node_settings_->endGroup();
        global_settings.sync();
    };

    /// Lambda to find node threaten as QObject by name
    auto findNode = [this](const QString &node_name, const QString &type)->QObject* {
        QObject *ptr;
        if(type.toLower()=="sensor") {
            try {
                ptr = sensor_container_->getNode(node_name);
            } catch (std::runtime_error e) {
                QString msg = "Cannot create connection: node " + node_name + "not found";
                throw new std::runtime_error(msg.toStdString());
            }
        } else if(type.toLower() == "broker") {
            try {
                ptr = broker_container_->getNode(node_name);
            } catch (std::runtime_error e) {
                QString msg = "Cannot create connection: node " + node_name + "not found";
                throw new std::runtime_error(msg.toStdString());
            }
        } else if(type.toLower() == "connectivity") {
            try {
                ptr = connectivity_container_->getNode(node_name);
            } catch (std::runtime_error e) {
                QString msg = "Cannot create connection: node " + node_name + "not found";
                throw new std::runtime_error(msg.toStdString());
            }
        } else return nullptr;

        return ptr;
    };


    ///Encapsulates routine of making connection between nodes.
    auto makeConnection = [this](QObject* out, const QString &out_type, QObject* in, const QString &in_type)->void {
        QObject *ptr;
        // Determine type of out node
        if(out_type.toLower()=="sensor") {
            SensorNode* sn = dynamic_cast<SensorNode*>(out);
            if(in_type.toLower() == "broker") {
                BrokerNode* bn = dynamic_cast<BrokerNode*>(in);
                connect(sn, &SensorNode::sensorDataAvaliable, bn, &BrokerNode::processData, Qt::ConnectionType::QueuedConnection );
                connect(this, &ApplicationContextLoader::startNodes, bn, &BrokerNode::start, Qt::ConnectionType::QueuedConnection);

            } else if(in_type.toLower() == "connectivity") {
                ConnectivityNode* cn = dynamic_cast<ConnectivityNode*>(in);
                connect(sn, &SensorNode::sensorDataAvaliable, cn, &ConnectivityNode::sendData, Qt::ConnectionType::QueuedConnection );
                connect(this, &ApplicationContextLoader::startNodes, cn, &ConnectivityNode::start, Qt::ConnectionType::QueuedConnection);

            } else {
                qDebug()<<TAG<<": Cannot connect: "<<in_type<<" is not proper node type.";
                return;
            }
            connect(this, &ApplicationContextLoader::startNodes, sn, &SensorNode::start, Qt::ConnectionType::QueuedConnection);

        } else if(out_type.toLower() == "broker") {
            BrokerNode* bn = dynamic_cast<BrokerNode*>(out);
            if(in_type.toLower() == "broker") {
                BrokerNode* bn2 = dynamic_cast<BrokerNode*>(in);
                connect(bn, &BrokerNode::dataProcessed, bn2, &BrokerNode::processData, Qt::ConnectionType::QueuedConnection );
                connect(this, &ApplicationContextLoader::startNodes, bn2, &BrokerNode::start, Qt::ConnectionType::QueuedConnection);

            } else if(in_type.toLower() == "connectivity") {
                ConnectivityNode* cn = dynamic_cast<ConnectivityNode*>(in);
                connect(bn, &BrokerNode::dataProcessed, cn, &ConnectivityNode::sendData, Qt::ConnectionType::QueuedConnection );
                connect(this, &ApplicationContextLoader::startNodes, cn, &ConnectivityNode::start, Qt::ConnectionType::QueuedConnection);

            } else {
                qDebug()<<TAG<<": Cannot connect: "<<in_type<<" is not proper node type.";
                return;
            }
            connect(this, &ApplicationContextLoader::startNodes, bn, &BrokerNode::start, Qt::ConnectionType::QueuedConnection);

        } else if(out_type.toLower() == "connectivity") {
            ConnectivityNode* cn = dynamic_cast<ConnectivityNode*>(out);
            if(in_type.toLower() == "broker") {
                BrokerNode* bn = dynamic_cast<BrokerNode*>(in);
                connect(cn, &ConnectivityNode::dataReceived, bn, &BrokerNode::processData, Qt::ConnectionType::QueuedConnection );
                connect(this, &ApplicationContextLoader::startNodes, bn, &BrokerNode::start, Qt::ConnectionType::QueuedConnection);

            } else {
                qDebug()<<TAG<<": Cannot connect: "<<in_type<<" is not proper node type.";
                return;
            }
            connect(this, &ApplicationContextLoader::startNodes, cn, &ConnectivityNode::start, Qt::ConnectionType::QueuedConnection);

        } else qDebug()<<TAG<<": Cannot connect: "<<out_type<<" is not proper node type.";
    };

    /// Load plugins and instantiate nodes
    QMap<QString, QStringList> connections_by_name;
    foreach (const QString &name, node_name_list) {
        node_settings_->beginGroup(name);
        QString type = node_settings_->value(NODE_TYPE_KEY).toString();
        QString lib_filename = node_settings_->value(NODE_LIB_FILENAME_KEY).toString();
        QString classname = node_settings_->value(NODE_CLASSNAME_KEY).toString();
        connections_by_name.insert(name, node_settings_->value(NODE_CONNECTIONS_KEY).toStringList());
        node_settings_->endGroup();

        ///Copy settings to global scope (they will be necessarry during node creation)
        copySettingsToGlobal(name);

        try{
        /// Instantiate node
            if(type.toLower()=="sensor") {
                SensorNodeFactory * nf = plugin_loader_->loadPlugin<SensorNodeFactory>(lib_filename);
                sensor_container_->registerFactory(nf->getNodeClassName(), nf);
                SensorNode* node = nf->createNode(name);
                sensor_container_->addNode(node->getName(), node);
            } else if(type.toLower() == "broker") {
                BrokerNodeFactory * nf = plugin_loader_->loadPlugin<BrokerNodeFactory>(lib_filename);
                broker_container_->registerFactory(nf->getNodeClassName(), nf);
                BrokerNode* node = nf->createNode(name);
                broker_container_->addNode(node->getName(), node);
            } else if(type.toLower() == "connectivity") {
                ConnectivityNodeFactory * nf = plugin_loader_->loadPlugin<ConnectivityNodeFactory>(lib_filename);
                connectivity_container_->registerFactory(nf->getNodeClassName(), nf);
                 ConnectivityNode* node = nf->createNode(name);
                connectivity_container_->addNode(node->getName(), node);
            } else continue;
        } catch (std::runtime_error e) {
            qDebug()<<TAG<<": loadApplicationContext()- Error when creating node: "<<name<<" of class: "<<classname<<". Rolling back settings change.";
            global_settings.beginGroup(name);
            global_settings.remove("");
            global_settings.endGroup();
        }
    }

    /// Load and create connections
    foreach (const QString &name, connections_by_name.keys()) {
        QObject* out;
        QString out_type = node_settings_->value(name+"/"+NODE_TYPE_KEY).toString();
        out = findNode(name,out_type);
        if(out == nullptr) {
            QString errmsg = "Unable to connect. Node of name: "+name+" not found.";
            qDebug()<<TAG<<": "<<errmsg;
        }

        foreach(const QString &connection, connections_by_name[name]) {
            QString in_type = node_settings_->value(connection+"/"+NODE_TYPE_KEY).toString();
            QObject *in = findNode(connection, in_type);
            if(in == nullptr) {
                QString errmsg = "Unable to connect. Node of name: "+connection+" not found.";
                qDebug()<<TAG<<": "<<errmsg;
            }
            makeConnection(out, out_type, in, in_type);

            qDebug()<<TAG<<": connection made between "+name+" and "+connection;
        }

    }
    emit startNodes();
}

void ApplicationContextLoader::loadTestContext()
{
    assertNodeContainerExists();
    QString sts_factory_name = "SystemTelemetrySensor";
    QString sensor_name = "SysTelemetrySensor1";
}

void ApplicationContextLoader::setPluginLoader(PluginLoader *plugin_loader)
{
    plugin_loader_ = plugin_loader;
}

void ApplicationContextLoader::setSensorContainer(NodeContainer<SensorNode, SensorNodeFactory> *sensor_container)
{
    sensor_container_ = sensor_container;
}

void ApplicationContextLoader::setBrokerContainer(NodeContainer<BrokerNode, BrokerNodeFactory> *broker_container)
{
    broker_container_ = broker_container;
}

void ApplicationContextLoader::setConnectivityContainer(NodeContainer<ConnectivityNode, ConnectivityNodeFactory> *connectivity_container)
{
    connectivity_container_ = connectivity_container;
}

void ApplicationContextLoader::assertNodeContainerExists()
{
    if( this->sensor_container_ == nullptr ||
        this->broker_container_ == nullptr ||
        this->connectivity_container_ == nullptr)
        throw new std::runtime_error("No NodeContainer specified.");
}
