#ifndef FILEQUERY_H
#define FILEQUERY_H

#include <QString>
#include <memory>

extern "C"
{
    #include "cdb.h"
}

class FileQuery
{
public:
    FileQuery(const QString& fileName);
    ~FileQuery();
    bool containsKey(QString key);
    QByteArray getValue(QString key);
    QByteArray* getValuePointer(QString key);

private:
    QStringView dbFile;
    int file;
    std::unique_ptr<cdb> cdbp;
};

#endif // FILEQUERY_H
