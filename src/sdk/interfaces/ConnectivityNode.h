#ifndef CONNECTIVITYNODE_H
#define CONNECTIVITYNODE_H
#include <QObject>
#include <QString>
#include <dataitem.h>

class ConnectivityNode : public QObject
{
    Q_OBJECT
public:
    explicit ConnectivityNode(const QString& name, QObject *parent = 0) : QObject(parent) {Q_UNUSED(name);}
    virtual ~ConnectivityNode() {}
    virtual QString getName() = 0;


public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void sendData(DataItem data) = 0;

signals:
    void dataReceived(DataItem data);
    void onStopped();
};

#endif // CONNECTIVITYNODE_H
