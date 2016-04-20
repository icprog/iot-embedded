#include "IotBroker.h"
#include <QDebug>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>

const QString IoTBroker::TAG = "IoTBroker";
const QString IoTBroker::IOT_BROKER_ID_MAPPING_KEY = "sensorId";

IoTBroker::IoTBroker(const QString& name, QObject *parent) : BrokerNode(name, parent),
                                                                 name_(name)
{
    settings_.beginGroup(name_);
    settings_.beginGroup(IOT_BROKER_ID_MAPPING_KEY);
    QStringList nodes = settings_.childGroups();
    foreach (const QString &node, nodes) {
        settings_.beginGroup(node);
        QStringList mappings = settings_.childKeys();
        foreach(const QString &key, mappings) {
            sensor_id_mapping_.insert(node+"/"+key, settings_.value(key).toInt());
        }
        settings_.endGroup();
    }

}

QString IoTBroker::getName()
{
    return name_;
}

void IoTBroker::start()
{

}

void IoTBroker::stop()
{

}

void IoTBroker::processData(DataItem data)
{
    qDebug()<<TAG<<": processData() from thread: "<<QThread::currentThreadId();

    int sensor_id = sensor_id_mapping_[data.senderId()];
    DataItem response = messageFormattingStrategy_->formatMessage(data, sensor_id, name_);

    qDebug()<<TAG<<": processData(): "<<response.payload()["data"].toString();
    emit dataProcessed(response);
}

void IoTBroker::setMessageFormattingStrategy(MessageFormattingStrategy *mfs)
{
    messageFormattingStrategy_ = mfs;
}
