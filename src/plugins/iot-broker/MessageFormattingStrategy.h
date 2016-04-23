#ifndef MESSAGEFORMATTINGSTRATEGY_H
#define MESSAGEFORMATTINGSTRATEGY_H
#include <dataitem.h>

/**
 * @brief The MessageFormattingStrategy interface
 * @details Encapsulates message formatting strategy
 */
class MessageFormattingStrategy
{
public:
    virtual ~MessageFormattingStrategy() {}

    /**
     * @brief formatMessage Formats message
     * @param source Message to be formatted
     * @param sender_id Sender node ID in IoT Platform system
     * @param broker_name Broker node name
     * @return resulting DataItem
     */
    virtual DataItem formatMessage(DataItem source, int sender_id, QString broker_name) = 0;
};

#endif // MESSAGEFORMATTINGSTRATEGY_H
