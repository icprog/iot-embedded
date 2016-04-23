#ifndef QWEBSOCKETWRAPPER_H
#define QWEBSOCKETWRAPPER_H
#include <QObject>
#include <QWebSocket>
#include "socket/Socket.h"

/**
 * @brief The QWebSocketWrapper class
 * @details Wraps QWebSocket into Socket interface
 */
class QWebSocketWrapper : public Socket
{
    Q_OBJECT
public:
    /**
     * @brief QWebSocketWrapper Constructor
     * @param parent Socket parent. Should be instance of SocketEndpoint.
     */
    explicit QWebSocketWrapper(QObject *parent = 0);
    virtual ~QWebSocketWrapper();

    /**
     * @brief connect Connects to host specified with @ref setDestination method
     */
    virtual void connect() override;

    /**
     * @brief disconnect Closes the connection
     */
    virtual void disconnect() override;

    /**
     * @brief setDestination Sets remote host to connect
     * @param hostname Host URL
     * @param port_number Port number. If port is specified in URL, pass 0;
     */
    virtual void setDestination(QString hostname, qint64 port_number) override;
public slots:

    /**
     * @brief send Sends binary data via WebSocket
     * @param data Data to send
     */
    virtual void send(QByteArray data) override;

private:
    QWebSocket* socket_;
    QUrl url_;

private slots:
    void onMessageReceived(const QByteArray &msg);
    void onDisconnect();
};

#endif // QWEBSOCKETWRAPPER_H
