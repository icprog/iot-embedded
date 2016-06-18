#ifndef JSONMESSAGEFORMATTER_H
#define JSONMESSAGEFORMATTER_H
#include <QObject>
#include "MessageFormattingStrategy.h"

/**
 * @brief The JsonMessageFormatter class
 * @details Converts data item payload to JSON file. Keys of payload map are converted to JSON document key-value pairs.
 */
class JsonMessageFormatter : public QObject, public MessageFormattingStrategy
{
public:
    explicit JsonMessageFormatter(QObject* parent = 0);
//    virtual ~JsonMessageFormatter() {}

    /**
     * @brief formatMessage Formats message
     * @param source Message to be formatted
     * @param sender_id Sender node ID in IoT Platform system
     * @param broker_name Broker node name
     * @return resulting DataItem
     */
    DataItem formatMessage(DataItem source, int sender_id, QString broker_name) override;
};

#endif // JSONMESSAGEFORMATTER_H
