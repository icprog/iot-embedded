#ifndef QWEBSOCKETWRAPPER_H
#define QWEBSOCKETWRAPPER_H
#include <QObject>
#include <QWebSocket>
#include "socket/Socket.h"

class QWebSocketWrapper : public Socket
{
    Q_OBJECT
public:
    explicit QWebSocketWrapper(QObject *parent = 0);
    virtual ~QWebSocketWrapper();
    virtual void connect() override;
    virtual void disconnect() override;
    virtual void setDestination(QString hostname, qint64 port_number) override;
public slots:
    virtual void send(QByteArray data) override;

private:
    QWebSocket* socket_;
    QUrl url_;

private slots:
    void onMessageReceived(const QByteArray &msg);
};

#endif // QWEBSOCKETWRAPPER_H
