#ifndef BROKERNODE_H
#define BROKERNODE_H
#include <QObject>
#include <QString>
#include <dataitem.h>

class BrokerNode : public QObject
{
    Q_OBJECT
public:
    explicit BrokerNode(const QString& name, QObject *parent = 0) : QObject(parent) {}
    virtual ~BrokerNode() {}
    virtual QString getName() = 0;


public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void processData(DataItem data) = 0;

signals:
    void dataProcessed(DataItem data);
    void onStopped();
};

#endif // NODE_H
