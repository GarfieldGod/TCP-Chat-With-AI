#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QMap>
#include <QTcpSocket>
#include <QListWidgetItem>

#include "myui.h"
#include "databasemanager.h"

class UserManager
{
public:
    UserManager();
    static void Outlist(QListWidget *&list,int column,QString condition);
    static QString OutlistreturnOne(QListWidget *&list,int column,QString condition);
    static void ChangeStatus(QListWidget *&list,QString Name,QString status,QString color);
    static void UserStatusChangeToDatabase(QString UserName,QString OnlineTime,bool status);
    static QMap<QString,QTcpSocket*>* OnlineTcp;
    static QMap<QTcpSocket*,QString>* OnlineUser;
    static void SendToAllOnlineUsers(QString Message);
};

#endif // USERMANAGER_H
