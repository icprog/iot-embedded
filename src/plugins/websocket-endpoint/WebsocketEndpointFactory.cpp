#include "WebsocketEndpointFactory.h"
#include <QDebug>
#include <QThread>
#include "socket/SocketEndpoint.h"

const QString WebsocketEndpointFactory::TAG = "WebsocketEndpointFactory";

WebsocketEndpointFactory::WebsocketEndpointFactory(QObject *parent) : QObject(parent)
{

}

ConnectivityNode *WebsocketEndpointFactory::createNode(const QString &node_name)
{
    qDebug()<< TAG << ": createNode() from thread: " << QThread::currentThreadId();
    QThread *node_thread = new QThread(this);
    node_thread->start();
    SocketEndpoint *se = new SocketEndpoint(node_name);
//    se->setSocket(new Socket());
    ConnectivityNode *node = se;
    se->moveToThread(node_thread);
    qDebug()<<TAG<<": Node created and moved to dedicated thread." ;
    return node;
}

QByteArray WebsocketEndpointFactory::getNodeClassName()
{
    return "WebsocketEndpoint";
}
