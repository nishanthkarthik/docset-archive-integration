#include "contentsocket.h"

#include <QObject>
#include <QtDebug>

ContentSocket::ContentSocket(QObject* parent, QTcpSocket* socket) : QObject (parent), socket(socket)
{
    cdb = std::unique_ptr<FileQuery>(new FileQuery("sqlite.cdb"));
}

ContentSocket::~ContentSocket()
{
}

void ContentSocket::TxRx()
{
    QString reqHeaders(socket->readAll());

    static const QRegularExpression regExp = QRegularExpression(QString("^GET \\/([^\\s]+\\.(\\w+)) HTTP\\/\\d\\.\\d"));

    QRegularExpressionMatch match = regExp.match(reqHeaders);
    if (!match.hasMatch() || !socket->isWritable()) return;

    const QString path = match.captured(1);
    const QString ext(match.captured(2));

    const QByteArray headers = QByteArray("HTTP/1.1 200 OK\r\nConnection: close\r\n");

    socket->write(headers);
    socket->write(mimeType(ext).toUtf8());

    static QCache<QString, QByteArray> cache(1000);
    if (cache.contains(path)) {
        socket->write(*cache[path]);
    } else {
        QByteArray* result = cdb.get()->getValuePointer(path);
        cache.insert(path, result);
        socket->write(*result);
    }
    socket->disconnectFromHost();
}

void ContentSocket::ClosingClient()
{
    socket->deleteLater();
}

const QString& ContentSocket::mimeType(const QString &ext)
{
    static const QString html("text/html\r\n");
    static const QString css("text/css\r\n");
    static const QString txt("text/plain\r\n");
    static const QString js("application/javascript\r\n");

    if (ext == "html")
        return html;
    else if (ext == "css")
        return css;
    else if (ext == "js")
        return js;
    else
        return txt;
}
