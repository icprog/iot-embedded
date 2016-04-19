#ifndef NODECONTAINER_H
#define NODECONTAINER_H

#include <QObject>
#include <QMap>
#include <type_traits>
#include <SensorNode.h>
#include <SensorNodeFactory.h>
#include <BrokerNode.h>
#include <BrokerNodeFactory.h>
#include <ConnectivityNode.h>
#include <ConnectivityNodeFactory.h>

class NodeContainer : public QObject
{
    Q_OBJECT
public:
    explicit NodeContainer(QObject *parent = 0);
    ~NodeContainer();

    /*template<typename T>
    T* getNode(const QString &name) {
        using std::is_same;

        if(is_same<T, BrokerNode>::value)
            if(broker_nodes_.contains(name))
                return broker_nodes_[name];
            else throw new std::runtime_error("Cannot find node");
        else if(is_same<T, SensorNode>::value)
            if(sensor_nodes_.contains(name))
                return sensor_nodes_[name];
            else throw new std::runtime_error("Cannot find node");
        else if(is_same<T, ConnectivityNode>::value)
            if(connectivity_nodes_.contains(name))
                return connectivity_nodes_[name];
            else throw new std::runtime_error("Cannot find node");
        else throw new std::runtime_error("Invalid type given");
    }

    template<typename F>
    F* getFactory(const QString &classname) {
        using std::is_same;

        QMap<QString, F>* map;
        if(is_same<F, BrokerNodeFactory>::value)
            map = &broker_node_factories_;
        else if(is_same<F, SensorNodeFactory>::value)
            map = &sensor_node_factories_;
        else if(is_same<F, ConnectivityNodeFactory>::value)
            map = &connectivity_node_factories_;
        if(map->contains(classname))
        {
            return map[classname];
        }
        else throw new std::runtime_error("Cannot find node factory");
    }*/

    SensorNode* getSensor(const QString &name);
    BrokerNode* getBroker(const QString &name);
    ConnectivityNode* getConnectivityNode(const QString &name);

    SensorNodeFactory* getSensorFactory(const QString &name);
    BrokerNodeFactory* getBrokerFactory(const QString &name);
    ConnectivityNodeFactory* getConnectivityFactory(const QString &name);


    bool loadNodeFactory(QString &file_name);
    bool loadNodeFactoryTestSet();

    void registerNode(SensorNode *node);
    void registerNode(BrokerNode *node);
    void registerNode(ConnectivityNode *node);

signals:

public slots:

private:
//    QMap<QString, Node*> nodes_;
//    QMap<QString, NodeFactory*> factories_;

    QMap<QString, SensorNode*> sensor_nodes_;
    QMap<QString, BrokerNode*> broker_nodes_;
    QMap<QString, ConnectivityNode*> connectivity_nodes_;

    QMap<QString, SensorNodeFactory*> sensor_node_factories_;
    QMap<QString, BrokerNodeFactory*> broker_node_factories_;
    QMap<QString, ConnectivityNodeFactory*> connectivity_node_factories_;

};

#endif // NODECONTAINER_H
