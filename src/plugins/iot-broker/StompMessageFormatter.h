#ifndef STOMPMESSAGEFORMATTER_H
#define STOMPMESSAGEFORMATTER_H

#include <QObject>
#include "MessageFormattingStrategy.h"
#include "JsonMessageFormatter.h"
class StompMessageFormatter : public QObject, public MessageFormattingStrategy
{
public:
    explicit StompMessageFormatter(QObject *parent = 0);
    virtual ~StompMessageFormatter() {}
    virtual DataItem formatMessage(DataItem source, int sender_id, QString broker_name);
private:
    JsonMessageFormatter *formatter;
};

#endif // STOMPMESSAGEFORMATTER_H
