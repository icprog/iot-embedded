#ifndef IOTBROKER_H
#define IOTBROKER_H

#include <QObject>
#include <QSettings>
#include <BrokerNode.h>
#include "MessageFormattingStrategy.h"

/**
 * @brief The IoTBroker class
 * @details IoT platform broker node. Receives data from sensors, formats them to JSON and STOMP format
 *          acceptable by server
 */
class IoTBroker : public BrokerNode
{
    Q_OBJECT
public:
    /**
     * @brief IoTBroker constructor
     * @param name Node name
     * @param parent Node parent
     */
    explicit IoTBroker(const QString& name, QObject *parent = 0);
    virtual ~IoTBroker() {}

    /**
     * @brief getName Returns node name.
     */
    virtual QString getName() override final;

    /**
     * @brief setMessageFormattingStrategy Sets message formatting strategy.
     * @param mfs pointer to MessageFormattingStrategy object
     */
    void setMessageFormattingStrategy(MessageFormattingStrategy *mfs);

public slots:

    /**
     * @brief start Starts processing
     * @note Because of event-driven processing nature, this function has no effect.
     */
    virtual void start() override;

    /**
     * @brief stop Stop processing
     * @note Because of event-driven processing nature, this function has no effect.
     */
    virtual void stop() override;

    /**
     * @brief processData Performs data processing - extracts payload, formats to JSON/STOMP and emits formated item.
     * @param data Data Item
     */
    virtual void processData(DataItem data) override;

private:
   static const QString TAG;
   static const QString IOT_BROKER_ID_MAPPING_KEY;
   QString name_;
   QSettings settings_;
   MessageFormattingStrategy *messageFormattingStrategy_;

   QMap<QString, int> sensor_id_mapping_;

};

#endif // IOTBROKER_H
