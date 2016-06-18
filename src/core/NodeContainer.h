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


/**
 * @brief Template class for node container
 * @param Node Node type
 * @param Factory NodeFactory type.
 * @note NodeFactory must be able to produce Node instances, otherwise errors will occur at compile time.
 */
template<typename Node, typename Factory>
class NodeContainer : public QObject
{
public:
    explicit NodeContainer(QObject *parent = 0) : QObject(parent) {}
    ~NodeContainer() {}

    Node* getNode(const QString &name){
        if(nodes_.contains(name))
            return nodes_[name];
        else throw new std::runtime_error("Node not found");
    }

    Factory* getFactory(const QString &name){
        if(factories_.contains(name))
            return factories_[name];
        else throw new std::runtime_error("Factory not found");
    }

    void registerFactory(const QString &name, Factory* factory){
        factories_.insert(name, factory);
    }

    void addNode(const QString &name, Node* node){
        nodes_.insert(name, node);
    }

private:
    QMap<QString, Node*> nodes_;
    QMap<QString, Factory*> factories_;
};

#endif // NODECONTAINER_H
