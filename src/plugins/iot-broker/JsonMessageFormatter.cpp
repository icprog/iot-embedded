#include "JsonMessageFormatter.h"
#include <QJsonObject>
#include <QJsonDocument>

JsonMessageFormatter::JsonMessageFormatter(QObject *parent) : QObject(parent)
{

}

DataItem JsonMessageFormatter::formatMessage(DataItem source, int sender_id, QString broker_name)
{
    QJsonObject json;
    json["id"] = sender_id;
    json["time"] = source.payload()["time"].toLongLong();
    json["value"] = source.payload()["value"].toDouble();
    DataItem result;
    result.setSenderId(broker_name.toUtf8());
    result.setSendTime(QDateTime::currentDateTime());
    result.setPayloadType("iot/json");
    result.payload().insert("data", QJsonDocument(json).toJson());
    return result;

}
