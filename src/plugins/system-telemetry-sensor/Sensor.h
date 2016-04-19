#ifndef SENSORENDPOINT_H
#define SENSORENDPOINT_H
#include <QObject>

#include <SensorNode.h>

#include "SensorWorker.h"


class Sensor : public SensorNode
{
    Q_OBJECT
public:
    explicit Sensor(const QString &name, QObject *parent = 0);
    QString getName() override final;
    QSettings *getSettings() const;

    void setWorker(SensorWorker *processor);

public slots:
    virtual void start() override;
    virtual void stop() override;

private slots:
    void onSensorDataAvaliable(DataItem data);

private:
    SensorWorker* processor_;
    const static QString TAG;

protected:
    QString name_;
    QSettings *settings_;
};

#endif // SENSORENDPOINT_H
