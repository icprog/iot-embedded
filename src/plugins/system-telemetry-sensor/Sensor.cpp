#include "Sensor.h"
#include <QDebug>
#include <QThread>

const QString Sensor::TAG = "SensorEndpoint";
Sensor::Sensor(const QString &name, QObject *parent) : SensorNode(name, parent),
                                                                    name_(name)
{
    this->settings_ = new QSettings(this);
}

QString Sensor::getName()
{
    return name_;
}

void Sensor::setWorker(SensorWorker *processor)
{
    processor_ = processor;
    processor_->setParent(this);
    processor_->setNodeName(this->name_);
    connect(processor, &SensorWorker::dataReady, this, &Sensor::onSensorDataAvaliable);
}

void Sensor::start()
{
    qDebug()<<TAG<<": start() from thread: "<<QThread::currentThreadId();
    processor_->start();
}

void Sensor::stop()
{
    qDebug()<<TAG<<": stop() from thread: "<<QThread::currentThreadId();
    processor_->stop();
    emit onStopped();
}

void Sensor::onSensorDataAvaliable(DataItem data)
{
    data.setSendTime(QDateTime::currentDateTime());
    emit sensorDataAvaliable(data);
}

QSettings *Sensor::getSettings() const
{
    return settings_;
}
