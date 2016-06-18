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
    /**
     * @brief DataItem Default constructor
     */
    DataItem();

    /**
     * @brief payload Payload map getter
     */
    QVariantMap &payload() ;

    /**
     * @brief setPayload Payload map setter
     */
    void setPayload(const QVariantMap &payload);

    /**
     * @brief sendTime packet send time getter
     * @note sendTime field is a property of DataItem, not the payload itself
     */
    QDateTime sendTime() const;

    /**
     * @brief sendTime packet send time setter
     * @note sendTime field is a property of DataItem, not the payload itself
     */
    void setSendTime(const QDateTime &send_time);

    /**
     * @brief senderId Sender node name getter.
     */
    QByteArray senderId() const;

    /**
     * @brief setSenderId Sender node name setter
     */
    void setSenderId(const QByteArray &sender_id);

    /**
     * @brief payloadType Payload type getter
     */
    QByteArray payloadType() const;

    /**
     * @brief payloadType Payload type setter
     */
    void setPayloadType(const QByteArray &payload_type);

private:
    QByteArray payload_type_;
    QByteArray sender_id_;
    QDateTime  send_time_;
    QVariantMap payload_;
};

Q_DECLARE_METATYPE(DataItem)

#endif // DATAITEM_H
