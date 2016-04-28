#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QByteArray>

/**
 * @brief The Socket interface
 * @details Common interface for sockets (TCP, UDP, SSL, Websockets etc.)
 */
class Socket : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Socket Constructor
     * @param parent Socket parent
     */
    explicit Socket(QObject *parent = 0) : QObject(parent) {}
    virtual ~Socket() {}

    /**
     * @brief connect Connect to host specified with @ref setDestination() method.
     */
    virtual void connect() = 0;

    /**
     * @brief disconnect Disconnect and close socket.
     */
    virtual void disconnect() = 0;

    /**
     * @brief setDestination Set socket host
     * @param hostname Host name or IP literal
     * @param port_number Port number;
     */
    virtual void setDestination(QString hostname, qint64 port_number) = 0;

signals:
    /**
     * @brief dataReceived Signal emitted on data receival.
     * @param data Received data
     */
    void dataReceived(QByteArray data);

    /**
     * @brief disconnected Signal emitted on disconnect.
     * @param reason Reason of disconnect.
     */
    void disconnected(QString reason);

public slots:

    /**
     * @brief send Sends given data via socket.
     * @param data Data to send.
     */
    virtual void send(QByteArray data) = 0;
};

#endif // SOCKET_H
