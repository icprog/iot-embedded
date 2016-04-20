#include "IoTBrokerFactory.h"
#include <QThread>
#include <QDebug>
#include <IotBroker.h>

#include "JsonMessageFormatter.h"
#include "StompMessageFormatter.h"

const QString IoTBrokerFactory::TAG = "IoTBrokerFactory";

IoTBrokerFactory::IoTBrokerFactory(QObject *parent) : QObject(parent)
{

}

BrokerNode *IoTBrokerFactory::createNode(const QString &node_name)
{
    qDebug()<< TAG << ": createNode() from thread: " << QThread::currentThreadId();
    QThread *thread = new QThread(this);
    thread->start();
    IoTBroker *bn = new IoTBroker(node_name);
    bn->setMessageFormattingStrategy(new StompMessageFormatter(bn));
    BrokerNode *node = bn;
    node->moveToThread(thread);
    qDebug()<<TAG<<": Node created and moved to dedicated thread." ;
    return node;
}

QByteArray IoTBrokerFactory::getNodeClassName()
{
    return "IoTBroker";
}
