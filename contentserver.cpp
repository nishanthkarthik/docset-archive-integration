#include "contentserver.h"
#include "contentsocket.h"

#include <QtDebug>

ContentServer::ContentServer(QObject* parent) : QObject(parent)
{
    server = new QTcpServer(parent);

    connect(server, &QTcpServer::newConnection, this, &ContentServer::ContentServerConnection);
    if (!server->listen(QHostAddress::Any, 8080)) {
        QDebug(QtMsgType::QtCriticalMsg) << "Could not start webserver";
    } else {
        QDebug(QtMsgType::QtInfoMsg) << "Started webserver at " << server->serverAddress();
    }
}

ContentServer::~ContentServer()
{
    server->close();
    delete server;
}

void ContentServer::ContentServerConnection()
{
    if (server->hasPendingConnections()) {
        ContentSocket socket(this->parent(), server->nextPendingConnection());
        connect(socket.socket, &QTcpSocket::readyRead, &socket, &ContentSocket::TxRx);
        connect(socket.socket, &QTcpSocket::disconnected, &socket, &ContentSocket::ClosingClient);
        while (!socket.socket->waitForDisconnected());
    }
}
