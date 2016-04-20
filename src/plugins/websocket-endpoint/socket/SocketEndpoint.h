#ifndef SocketEndpoint_H
#define SocketEndpoint_H

#include <QObject>
#include <QSettings>
#include <ConnectivityNode.h>

#include "Socket.h"

class SocketEndpoint : public ConnectivityNode
{
    Q_OBJECT
public:
    explicit SocketEndpoint(const QString& name, QObject *parent = 0);
    virtual ~SocketEndpoint() {}
    virtual QString getName() override final;

    void setSocket(Socket *socket);

public slots:
    virtual void start();
    virtual void stop();
    virtual void sendData(DataItem data);

private:
   static const QString TAG;
   QSettings settings_;
   QString name_;
   Socket* socket_;

};

#endif // SocketEndpoint_H
