#ifndef OFFLINEMESSAGE_H
#define OFFLINEMESSAGE_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "usermanager.h"

class OfflineMessage
{
public:
    OfflineMessage();
    static void OfflineSend(QString Name);
    static void OfflineRead(QString p);
};

#endif // OFFLINEMESSAGE_H
