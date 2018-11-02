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
    explicit ContentSocket(QObject* parent = nullptr, QTcpSocket* socket = nullptr);
    ~ContentSocket();
public slots:
    void TxRx();
    void ClosingClient();
private:
    const QString& mimeType(const QString& ext);
public:
    QTcpSocket* socket;
private:
    QRegularExpression regExp;
    std::unique_ptr<FileQuery> cdb;
};

#endif // CONTENTSOCKET_H
