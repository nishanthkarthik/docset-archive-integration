#ifndef CONTENTSOCKET_H
#define CONTENTSOCKET_H

#include <QTcpSocket>
#include <QObject>
#include <QRegularExpression>
#include <QCache>

#include "filequery.h"

class ContentSocket : public QObject
{
    Q_OBJECT
public:
    explicit ContentSocket(QObject* parent, QTcpSocket* socket);
    ~ContentSocket();
public slots:
    void TxRx();
    void ClosingClient();
private:
    inline const QString& mimeType(const QString& ext);
public:
    QTcpSocket* socket;
private:
    std::unique_ptr<FileQuery> cdb;
};

#endif // CONTENTSOCKET_H
