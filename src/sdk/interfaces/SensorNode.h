#ifndef SENSORNODE_H
#define SENSORNODE_H
#include <QObject>
#include <QString>
#include <dataitem.h>

class SensorNode : public QObject
{
    Q_OBJECT
public:
    explicit SensorNode(const QString& name, QObject *parent = 0) : QObject(parent) {}
    virtual ~SensorNode() {}
    virtual QString getName() = 0;


public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

signals:
    void sensorDataAvaliable(DataItem data);
    void onStopped();
};

#endif // SENSORNODE_H
