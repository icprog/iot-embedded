#include "QWebSocketWrapper.h"
#include <QEventLoop>
#include <QDebug>

QWebSocketWrapper::QWebSocketWrapper(QObject *parent) : Socket(parent), socket_(nullptr)
{

//    socket_ = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, parent);
//    QObject::connect(socket_, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onMessageReceived(QByteArray)));
//  connect(sn, &SensorNode::sensorDataAvaliable, cn, &ConnectivityNode::sendData, Qt::ConnectionType::QueuedConnection );
}

QWebSocketWrapper::~QWebSocketWrapper()
{
    socket_->close(QWebSocketProtocol::CloseCode::CloseCodeAbnormalDisconnection, "Socket instance about to be destroyed. This may mean application was killed.");
    delete socket_;
}


void QWebSocketWrapper::connect()
{
    if(socket_)
        delete socket_;
    socket_ = new QWebSocket();

    QEventLoop loop;
    QObject::connect(socket_, &QWebSocket::connected, &loop, &QEventLoop::quit);
    QObject::connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), &loop, SLOT(quit()));
    QObject::connect(socket_, &QWebSocket::disconnected, this, &QWebSocketWrapper::onDisconnect);
    socket_->open(QUrl(url_));
    loop.exec(); //blocks untill either theSignalToWaitFor or timeout was fired
    if(socket_->error() != -1){
        QString err = "Unable to connect to host: "+url_.toString()+", reason: "+socket_->errorString() + " error code: " + QString::number(socket_->error());
        throw std::runtime_error(err.toStdString());
    }

}

void QWebSocketWrapper::disconnect()
{
//    socket_->close();
    delete socket_;
    socket_ = nullptr;
    emit disconnected("WebSocket connection terminated.");
}

void QWebSocketWrapper::setDestination(QString hostname, qint64 port_number)
{
    url_.setUrl(hostname);
    if(port_number)
        url_.setPort(port_number);
}

void QWebSocketWrapper::send(QByteArray data)
{
    socket_->sendBinaryMessage(data);
}

void QWebSocketWrapper::onMessageReceived(const QByteArray &msg)
{
    emit dataReceived(msg);
}

void QWebSocketWrapper::onDisconnect()
{
    emit disconnected("WebSocket connection terminated.");
}
