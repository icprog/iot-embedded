#include "StompMessageFormatter.h"
#include "qstomp.h"

StompMessageFormatter::StompMessageFormatter(QObject *parent) : QObject(parent)
{
    formatter = new JsonMessageFormatter(this);
}

DataItem StompMessageFormatter::formatMessage(DataItem source, int sender_id, QString broker_name)
{
    DataItem res = formatter->formatMessage(source, sender_id, broker_name);
    QStompResponseFrame stomp(QStompResponseFrame::ResponseType::ResponseMessage);
    stomp.setBody(res.payload()["data"].toString());
    res.payload().remove("data");
    res.payload().insert("data", stomp.toByteArray());
    return res;

}
