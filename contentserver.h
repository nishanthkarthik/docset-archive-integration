#ifndef CONTENTSERVER_H
#define CONTENTSERVER_H

#include <QCoreApplication>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class ContentServer : public QObject
{
    Q_OBJECT
public:
    explicit ContentServer(QObject *parent = nullptr);
    ~ContentServer();

public slots:
    void ContentServerConnection();

private:
    QTcpServer* server;
};

#endif // CONTENTSERVER_H
