#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QColumnView>

#include "myui.h"

class DataBaseManager
{
public:
    DataBaseManager();
    static void LoadAllUsers (QListWidget* &alluserlist);
    static bool connectToDatabase();
};
#endif // DATABASEMANAGER_H
