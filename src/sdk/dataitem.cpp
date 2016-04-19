#include "dataitem.h"

DataItem::DataItem()
{

}

QVariantMap &DataItem::payload()
{
    return payload_;
}

void DataItem::setPayload(const QVariantMap &payload)
{
    payload_ = payload;
}

QDateTime DataItem::sendTime() const
{
    return send_time_;
}

void DataItem::setSendTime(const QDateTime &send_time)
{
    send_time_ = send_time;
}

QByteArray DataItem::senderId() const
{
    return sender_id_;
}

void DataItem::setSenderId(const QByteArray &sender_id)
{
    sender_id_ = sender_id;
}

QByteArray DataItem::payloadType() const
{
    return payload_type_;
}

void DataItem::setPayloadType(const QByteArray &payload_type)
{
    payload_type_ = payload_type;
}
