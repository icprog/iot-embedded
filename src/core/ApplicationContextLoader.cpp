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

ApplicationContextLoader::ApplicationContextLoader(QObject *parent) : QObject(parent)
{
    this->node_container_ = nullptr;

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
                ptr = node_container_->getSensor(node_name);
            } catch (std::runtime_error e) {
                QString msg = "Cannot create connection: node " + node_name + "not found";
                throw new std::runtime_error(msg.toStdString());
            }
        } else if(type.toLower() == "broker") {
            try {
                ptr = node_container_->getBroker(node_name);
            } catch (std::runtime_error e) {
                QString msg = "Cannot create connection: node " + node_name + "not found";
                throw new std::runtime_error(msg.toStdString());
            }
        } else if(type.toLower() == "connectivity") {
            try {
                ptr = node_container_->getConnectivityNode(node_name);
            } catch (std::runtime_error e) {
                QString msg = "Cannot create connection: node " + node_name + "not found";
                throw new std::runtime_error(msg.toStdString());
            }
        } else return nullptr;

        return ptr;
    };

    ///Encapsulates routine of making connection between nodes.
    auto makeConnection = [](QObject* out, const QString &out_type, QObject* in, const QString &in_type)->void {
        QObject *ptr;
        // Determine type of out node
        if(out_type.toLower()=="sensor") {
            SensorNode* sn = dynamic_cast<SensorNode*>(out);
            if(in_type.toLower() == "broker") {
                BrokerNode* bn = dynamic_cast<BrokerNode*>(in);
                connect(sn, &SensorNode::sensorDataAvaliable, bn, &BrokerNode::processData, Qt::ConnectionType::QueuedConnection );
                bn->start();
            } else if(in_type.toLower() == "connectivity") {
                ConnectivityNode* cn = dynamic_cast<ConnectivityNode*>(in);
                connect(sn, &SensorNode::sensorDataAvaliable, cn, &ConnectivityNode::sendData, Qt::ConnectionType::QueuedConnection );
                cn->start();
            } else qDebug()<<TAG<<": Cannot connect: "<<in_type<<" is not proper node type.";
            sn->start();
        } else if(out_type.toLower() == "broker") {
            BrokerNode* bn = dynamic_cast<BrokerNode*>(out);
            if(in_type.toLower() == "broker") {
                BrokerNode* bn2 = dynamic_cast<BrokerNode*>(in);
                connect(bn, &BrokerNode::dataProcessed, bn2, &BrokerNode::processData, Qt::ConnectionType::QueuedConnection );
                bn2->start();
            } else if(in_type.toLower() == "connectivity") {
                ConnectivityNode* cn = dynamic_cast<ConnectivityNode*>(in);
                connect(bn, &BrokerNode::dataProcessed, cn, &ConnectivityNode::sendData, Qt::ConnectionType::QueuedConnection );
                cn->start();
            } else qDebug()<<TAG<<": Cannot connect: "<<in_type<<" is not proper node type.";
            bn->start();
        } else if(out_type.toLower() == "connectivity") {
            ConnectivityNode* cn = dynamic_cast<ConnectivityNode*>(out);
            if(in_type.toLower() == "broker") {
                BrokerNode* bn = dynamic_cast<BrokerNode*>(in);
                connect(cn, &ConnectivityNode::dataReceived, bn, &BrokerNode::processData, Qt::ConnectionType::QueuedConnection );
                bn->start();
            } else qDebug()<<TAG<<": Cannot connect: "<<in_type<<" is not proper node type.";
            cn->start();
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

        node_container_->loadNodeFactory(lib_filename);

        ///Copy settings to global scope (they will be necessarry during node creation)
        copySettingsToGlobal(name);

        try{
        /// Instantiate node
            if(type.toLower()=="sensor") {
                SensorNode* node = node_container_->getSensorFactory(classname)->createNode(name);
                node_container_->registerNode(node);
            } else if(type.toLower() == "broker") {
                BrokerNode* node = node_container_->getBrokerFactory(classname)->createNode(name);
                node_container_->registerNode(node);
            } else if(type.toLower() == "connectivity") {
                ConnectivityNode* node = node_container_->getConnectivityFactory(classname)->createNode(name);
                node_container_->registerNode(node);
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




}

void ApplicationContextLoader::loadTestContext()
{
    assertNodeContainerExists();
    QString sts_factory_name = "SystemTelemetrySensor";
    QString sensor_name = "SysTelemetrySensor1";
//    node_container_->loadNodeFactoryTestSet();
//    Node *sts1 = node_container_->getNodeFactory(sts_factory_name)->createNode(sensor_name);
//    node_container_->registerNode(sts1);
//    Pipeline *pipe = new OneToManyPipeline(this);
//    pipe->setInboundChannel(node_container_->getNode(sensor_name));

//    sts1->start();

}

void ApplicationContextLoader::setNodeContainer(NodeContainer *node_container)
{
    node_container_ = node_container;
}

void ApplicationContextLoader::assertNodeContainerExists()
{
    if(this->node_container_ == nullptr)
        throw new std::runtime_error("No NodeContainer specified.");
}
