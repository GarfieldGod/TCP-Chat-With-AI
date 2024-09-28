#include "databasemanager.h"

DataBaseManager::DataBaseManager()
{
    Class = "QMYSQL";
    Host = "124.220.199.82";
    Database = "GarfieldGod";
    User = "root";
    Password = "125820196";
}
DataBaseManager::~DataBaseManager()
{
    db.close();
}
bool DataBaseManager::connectToDatabase()
{
    db = QSqlDatabase::addDatabase(Class);
    db.setHostName(Host);
    db.setDatabaseName(Database);
    db.setUserName(User);
    db.setPassword(Password);

    if(!db.open()) return false;
    return true;
}
QString DataBaseManager::CheckIDandPassword(QString ID,QString Password)
{
    if(ID == "" || Password == "")  return "账号或密码不能为空";

    if(!connectToDatabase()) return "无法连接到数据库";
    QSqlQuery query;
    query.prepare("SELECT * FROM UserInfo WHERE ID = :username");
    query.bindValue(":username", ID);
    if (query.exec() && !query.next()) return "该用户不存在";

    query.prepare("SELECT * FROM UserInfo WHERE ID = :username AND Password = :password");
    query.bindValue(":username", ID);
    query.bindValue(":password", Password);
    if (query.exec() && query.next())
    {
        QString ID = query.value("ID").toString();
        QString Password = query.value("Password").toString();
        QString Status = query.value("Status").toString();

        qDebug()<<ID<<Password<<Status;
        if(Status == "在线"){
            return "该账号已在线！";
        }
        else {
            return "账号和密码正确";
        }
    }
    return "密码错误";
}
QString DataBaseManager::Register(QString username,QString account,QString password)
{
    if(username == "" || account == "" || password == "")  return "存在空项！";
    if(username.size()>=10) return "昵称过长！";
    if(account.size()>=20 ||password.size()>=20) return "用户名或密码过长！";
    if(!connectToDatabase()) return "无法连接到数据库";

    QSqlQuery query;
    query.prepare("SELECT * FROM UserInfo WHERE ID = :account");
    query.bindValue(":account", account);
    if (query.exec() && !query.next()) {
        //return "该用户不存在";
    }
    else return "该用户已存在！";

    query.prepare("Insert Into UserInfo values(:username,:account,:password,NULL,NULL,NULL);");
    query.bindValue(":username", username);
    query.bindValue(":account", account);
    query.bindValue(":password", password);
    if (query.exec()) return "注册成功";
    else return "注册失败，请重试";
}
