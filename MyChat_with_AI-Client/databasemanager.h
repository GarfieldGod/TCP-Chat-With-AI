#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QtDebug>

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager();
    bool connectToDatabase();
    QString CheckIDandPassword(QString ID,QString Password);
    QString Register(QString username,QString account,QString password);
private:
    QSqlDatabase db;
    QString Class;
    QString Host;
    QString Database;
    QString User;
    QString Password;
};

#endif // DATABASEMANAGER_H
