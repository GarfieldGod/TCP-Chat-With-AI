#ifndef CHATHISTORY_H
#define CHATHISTORY_H

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "myui.h"

class ChatHistory
{
public:
    ChatHistory();
    static void writeHistory(QString Name,QString p);
    static void readHistory(QString Name,QString UserName,QListWidget* parent);
};

#endif // CHATHISTORY_H
