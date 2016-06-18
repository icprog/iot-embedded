#include "SystemTelemetrySensorFactory.h"
#include <QDebug>
#include <QThread>
const QString SystemTelemetrySensorFactory::TAG = "SystemTelemetrySensorFactory";

SystemTelemetrySensorFactory::SystemTelemetrySensorFactory(QObject *parent) : QObject(parent)
{

}

SensorNode *SystemTelemetrySensorFactory::createNode(const QString &node_name)
{
    qDebug()<< TAG << ": createNode() from thread: " << QThread::currentThreadId();
    QThread *node_thread = new QThread(this);
    node_thread->start();
    Sensor *se = new Sensor(node_name);
    se->setWorker(new SystemTelemetryWorker(se->getName(), se));
    SensorNode *node = se;
    se->moveToThread(node_thread);
    qDebug()<<TAG<<": Node created and moved to dedicated thread." ;
    return node;
}

QByteArray SystemTelemetrySensorFactory::getNodeClassName()
{
    return "SystemTelemetrySensor";
}
