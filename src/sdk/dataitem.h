#ifndef DATAITEM_H
#define DATAITEM_H

#include <QVariant>
#include <QTime>
#include "dataitem_global.h"

/**
 * @brief The DataItem class
 * @details Common representation of data
 */
class IOT_SHARED_EXPORT DataItem
{
public:
    DataItem();


    QVariantMap &payload() ;
    void setPayload(const QVariantMap &payload);

    QDateTime sendTime() const;
    void setSendTime(const QDateTime &send_time);

    QByteArray senderId() const;
    void setSenderId(const QByteArray &sender_id);

    QByteArray payloadType() const;
    void setPayloadType(const QByteArray &payload_type);

private:
    QByteArray payload_type_;
    QByteArray sender_id_;
    QDateTime  send_time_;
    QVariantMap payload_;
};

Q_DECLARE_METATYPE(DataItem)

#endif // DATAITEM_H
