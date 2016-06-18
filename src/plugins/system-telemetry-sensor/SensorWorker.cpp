#include "SensorWorker.h"

SensorWorker::SensorWorker(const QString &name, QObject *parent) : QObject(parent)
{
    this->settings_ = new QSettings(this);
}

void SensorWorker::setNodeName(const QString &name)
{
    this->node_name_ = name;
}
