#include "usermanager.h"

QMap<QString,QTcpSocket*>* UserManager::OnlineTcp = new QMap<QString,QTcpSocket*>;
QMap<QTcpSocket*,QString>* UserManager::OnlineUser = new QMap<QTcpSocket*,QString>;

UserManager::UserManager()
{
}

void UserManager::UserStatusChangeToDatabase(QString UserName,QString Time,bool status)
{
    DataBaseManager:: connectToDatabase();
    QSqlQuery query;

    query.prepare("SELECT * FROM UserInfo WHERE ID = :username");
    query.bindValue(":username", UserName);
    if (!query.exec()){
        qDebug() << "读取数据库错误" << query.lastError().text();}

    if (query.first()){
        query.prepare("UPDATE UserInfo SET Status = :status, LastTimeOnline = :time WHERE ID = :name");
        query.bindValue(":time", Time);
        query.bindValue(":name", UserName);
        if(status) query.bindValue(":status", "在线");
        else query.bindValue(":status", "离线");

        if (!query.exec()){
           qDebug() << "用户登录写入到数据库错误" << query.lastError().text();
        }
        qDebug()<<"用户登录写入到数据库成功";
    }
}
void UserManager::ChangeStatus(QListWidget *&list,QString Name,QString status,QString color)
{
    for (int i = 0; i < list->count(); i++) {
        QListWidgetItem* itemtoremove = list->item(i);
        myrow * myWidget = qobject_cast<myrow *>(list->itemWidget(itemtoremove));
        if (myWidget && myWidget->content1->text() == Name)
        {
            myWidget->content3->setText(status);
            QString sheet = "color: " + color + ";";
            myWidget->content3->setStyleSheet(sheet);
        }
    }
}
void UserManager::Outlist(QListWidget *&list,int column,QString condition)
{
    for (int i = 0; i < list->count(); i++) {
        QListWidgetItem* itemtoremove = list->item(i);
        myrow * myWidget = qobject_cast<myrow *>(list->itemWidget(itemtoremove));
        switch(column)
        {
            case 1:if (myWidget && myWidget->content1->text() == condition){
                list->takeItem(list->row(itemtoremove));}break;
            case 2:if (myWidget && myWidget->content2->text() == condition){
                list->takeItem(list->row(itemtoremove));}break;
            case 3:if (myWidget && myWidget->content3->text() == condition){
                list->takeItem(list->row(itemtoremove));}break;
            default:break;
        }
    }
}
QString UserManager::OutlistreturnOne(QListWidget *&list,int column,QString condition){
    for (int i = 0; i < list->count(); i++) {
        QListWidgetItem* itemtoremove = list->item(i);
        myrow * myWidget = qobject_cast<myrow *>(list->itemWidget(itemtoremove));
        QString result = myWidget->content1->text();
        switch(column){
            case 1:if (myWidget && myWidget->content1->text() == condition){
                list->takeItem(list->row(itemtoremove));
                return result;}break;
            case 2:if (myWidget && myWidget->content2->text() == condition){
                list->takeItem(list->row(itemtoremove));
                return result;}break;
            case 3:if (myWidget && myWidget->content3->text() == condition){
                list->takeItem(list->row(itemtoremove));
                return result;}break;
            default:break;
        }
    }
    return NULL;
}
void UserManager::SendToAllOnlineUsers(QString Message)
{
    for (QMap<QString, QTcpSocket*>::iterator it = OnlineTcp->begin(); it != OnlineTcp->end(); ++it)
    {
        QTcpSocket* socket = it.value();
        socket->write(Message.toUtf8());
    }
    qDebug()<<"向全体在线用户发送："<<Message;
}
