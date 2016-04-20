#ifndef IOTBROKER_H
#define IOTBROKER_H

#include <QObject>
#include <QSettings>
#include <BrokerNode.h>
#include "MessageFormattingStrategy.h"

class IoTBroker : public BrokerNode
{
    Q_OBJECT
public:
    explicit IoTBroker(const QString& name, QObject *parent = 0);
    virtual ~IoTBroker() {}
    virtual QString getName() override final;
    void setMessageFormattingStrategy(MessageFormattingStrategy *mfs);

public slots:
    virtual void start() override;
    virtual void stop() override;
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
