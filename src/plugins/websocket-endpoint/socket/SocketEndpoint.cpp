#include "SocketEndpoint.h"
#include <QDebug>
#include <stdexcept>
const QString SocketEndpoint::TAG = "SocketEndpoint";
SocketEndpoint::SocketEndpoint(const QString &name, QObject *parent) : ConnectivityNode(name, parent),
                                                                             name_(name)
{
    settings_.beginGroup(name);
}

QString SocketEndpoint::getName()
{
    return name_;
}

void SocketEndpoint::start()
{
    QString url = settings_.value("url").toString();
    qint64 port_number = settings_.value("portNumber").toLongLong();
    if(url.isEmpty())
    {
        url = settings_.value("hostname").toString();
    }
    socket_->setDestination(url, port_number);
    try {
        socket_->connect();
    } catch (std::runtime_error e) {
        qDebug()<<TAG<<": start() - unable to open socket with given url: "<<url<<" and portnumber: "<<port_number<<".";
    }

    stop();

}

void SocketEndpoint::stop()
{
    try {
        socket_->disconnect();
    } catch (std::runtime_error e) {
        qDebug()<<TAG<<": stop() - unable to disconnect, reason: "<<e.what();
    }
}

void SocketEndpoint::sendData(DataItem data)
{
    try {
        socket_->send(data.payload()["data"].toByteArray());
    } catch (std::runtime_error e) {
        qDebug()<<TAG<<": sendData() - exception caught during sending, reason: "<<e.what();
    }
}

void SocketEndpoint::setSocket(Socket *socket)
{
    socket_ = socket;
}
