#ifndef STOMPMESSAGEFORMATTER_H
#define STOMPMESSAGEFORMATTER_H

#include <QObject>
#include "MessageFormattingStrategy.h"
#include "JsonMessageFormatter.h"
/**
 * @brief The StompMessageFormatter class
 * @details Formats message to JSON and then to STOMP
 */
class StompMessageFormatter : public QObject, public MessageFormattingStrategy
{
public:
    explicit StompMessageFormatter(QObject *parent = 0);
    virtual ~StompMessageFormatter() {}

    /**
     * @brief formatMessage Formats message
     * @param source Message to be formatted
     * @param sender_id Sender node ID in IoT Platform system
     * @param broker_name Broker node name
     * @return resulting DataItem
     */
    virtual DataItem formatMessage(DataItem source, int sender_id, QString broker_name);
private:
    JsonMessageFormatter *formatter;
};

#endif // STOMPMESSAGEFORMATTER_H
