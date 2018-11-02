#include "filequery.h"

#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <QtDebug>

extern "C"
{
    #include "cdb.h"
}

FileQuery::FileQuery(const QString &fileName)
{
    dbFile = fileName;
    file = open(fileName.toUtf8().constData(), O_RDONLY);
    cdbp = std::unique_ptr<cdb>(new cdb());
    cdb_init(cdbp.get(), file);
}

FileQuery::~FileQuery()
{
    cdb_free(cdbp.get());
    close(file);
}

bool FileQuery::containsKey(QString key)
{
    return cdb_find(cdbp.get(), key.toUtf8().constData(), static_cast<unsigned>(key.size())) > 0;
}

QByteArray FileQuery::getValue(QString key)
{
    if (cdb_find(cdbp.get(), key.toUtf8().constData(), static_cast<unsigned>(key.size())) > 0) {
        unsigned pos = cdb_datapos(cdbp.get());
        unsigned len = cdb_datalen(cdbp.get());
        QByteArray val = QByteArray(static_cast<int>(len), Qt::Initialization::Uninitialized);
        cdb_read(cdbp.get(), val.data(), len, pos);
        return val;
    }
    return QByteArray();
}

QByteArray* FileQuery::getValuePointer(QString key)
{
    if (cdb_find(cdbp.get(), key.toUtf8().constData(), static_cast<unsigned>(key.size())) > 0) {
        unsigned pos = cdb_datapos(cdbp.get());
        unsigned len = cdb_datalen(cdbp.get());
        QByteArray* val = new QByteArray(static_cast<int>(len), Qt::Initialization::Uninitialized);
        cdb_read(cdbp.get(), val->data(), len, pos);
        return val;
    }
    return nullptr;
}
