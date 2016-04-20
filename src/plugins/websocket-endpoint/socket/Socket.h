#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QByteArray>

class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = 0);
    virtual ~Socket() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void setDestination(QString hostname, qint64 port_number) = 0;

signals:
    void dataReceived(QByteArray data);

public slots:
    virtual void send(QByteArray data) = 0;
};

#endif // SOCKET_H
