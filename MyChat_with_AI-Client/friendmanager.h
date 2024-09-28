#ifndef FRIENDMANAGER_H
#define FRIENDMANAGER_H

#include <QObject>

#include <databasemanager.h>
#include "myui.h"

class FriendManager : public QObject
{
    Q_OBJECT
public:
    explicit FriendManager(QObject *parent = nullptr);
    static QVector<QVector<QString>> FriendList;
    static void LoadFriend (QListWidget* List);
    static void LoadFriend (QListWidget* list,QString Name,bool ifonline);
    static void ADDnewMessage(QListWidget* &list,QString Name);

signals:

};

#endif // FRIENDMANAGER_H
