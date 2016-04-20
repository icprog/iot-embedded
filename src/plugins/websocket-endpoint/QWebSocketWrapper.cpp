#include "QWebSocketWrapper.h"
#include <QEventLoop>

QWebSocketWrapper::QWebSocketWrapper(QObject *parent) : Socket(parent)
{

    socket_ = new QWebSocket(QString(), QWebSocketProtocol::Version8);
    QObject::connect(socket_, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onMessageReceived(QByteArray)));
//  connect(sn, &SensorNode::sensorDataAvaliable, cn, &ConnectivityNode::sendData, Qt::ConnectionType::QueuedConnection );
}

QWebSocketWrapper::~QWebSocketWrapper()
{
    socket_->close(QWebSocketProtocol::CloseCode::CloseCodeAbnormalDisconnection, "Socket instance about to be destroyed. This may mean application was killed.");
    delete socket_;
}


void QWebSocketWrapper::connect()
{
    QEventLoop loop;
    QObject::connect(socket_, &QWebSocket::connected, &loop, &QEventLoop::quit);
    QObject::connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), &loop, SLOT(quit()));
    socket_->open(url_);
    loop.exec(); //blocks untill either theSignalToWaitFor or timeout was fired
    if(!socket_->errorString().isEmpty()){
        QString err = "Unable to connect to host: "+url_.toString()+", reason: "+socket_->errorString();
        throw std::runtime_error(err.toStdString());
    }


}

void QWebSocketWrapper::disconnect()
{
    socket_->close();
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
