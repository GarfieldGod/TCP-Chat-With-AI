#include "databasemanager.h"

DataBaseManager::DataBaseManager()
{
}
bool DataBaseManager:: connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("124.220.199.82");
    db.setDatabaseName("GarfieldGod");
    db.setUserName("root");
    db.setPassword("125820196");

    if(!db.open()) {QMessageBox::critical(nullptr,"Database Error","错误！无法连接至数据库！ " + db.lastError().text());return false;}
    else qDebug()<<"数据库连接成功";
    return true;
}
void DataBaseManager::LoadAllUsers (QListWidget *&alluserlist)
{
    QSqlQuery query;
    query.exec("SELECT * FROM UserInfo");
    while(query.next())
    {
        myrow* A = new myrow(query.value(1).toString(),query.value(2).toString(),"离线",alluserlist);
        A->ToUi(alluserlist);
    }
}
