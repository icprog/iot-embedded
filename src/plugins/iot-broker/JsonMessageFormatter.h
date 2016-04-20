#ifndef JSONMESSAGEFORMATTER_H
#define JSONMESSAGEFORMATTER_H
#include <QObject>
#include "MessageFormattingStrategy.h"

class JsonMessageFormatter : public QObject, public MessageFormattingStrategy
{
public:
    explicit JsonMessageFormatter(QObject* parent = 0);
//    virtual ~JsonMessageFormatter() {}

    DataItem formatMessage(DataItem source, int sender_id, QString broker_name) override;
};

#endif // JSONMESSAGEFORMATTER_H
