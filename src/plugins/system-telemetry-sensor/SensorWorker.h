#ifndef SENSORPROCESSOR_H
#define SENSORPROCESSOR_H

#include <QObject>
#include <QTimer>
#include <QSettings>
#include "dataitem.h"

class SensorWorker : public QObject
{
    Q_OBJECT
public:
    explicit SensorWorker(const QString &name, QObject *parent = 0);

    void setNodeName(const QString &name);

signals:
    void dataReady(DataItem data);
    void signalStart(int delay);
    void signalStart();
    void signalStop();

public slots:
    virtual void onData(DataItem data)=0;
    virtual void stop() = 0;
    virtual void start() = 0;
protected:
    QTimer* timer_;
    QSettings* settings_;
    QString node_name_;
};

#endif // SENSORPROCESSOR_H
