#ifndef MESSAGEFORMATTINGSTRATEGY_H
#define MESSAGEFORMATTINGSTRATEGY_H
#include <dataitem.h>

class MessageFormattingStrategy
{
public:
    virtual ~MessageFormattingStrategy() {}
    virtual DataItem formatMessage(DataItem source, int sender_id, QString broker_name) = 0;
};

#endif // MESSAGEFORMATTINGSTRATEGY_H
