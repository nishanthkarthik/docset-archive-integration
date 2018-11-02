#include <QCoreApplication>

#include "contentserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ContentServer server;
    return a.exec();
}
