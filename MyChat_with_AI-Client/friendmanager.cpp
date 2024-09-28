#include "friendmanager.h"

QVector<QVector<QString>> FriendManager::FriendList;

FriendManager::FriendManager(QObject *parent) : QObject(parent)
{
}

void FriendManager::LoadFriend (QListWidget* List)
{
    List->clear();
    QSqlQuery query;
    query.exec("SELECT * FROM UserInfo");
    while(query.next())
    {
        if(query.value(4).toString() == "在线")
        {
            FriendBox* A = new FriendBox("",query.value(1).toString(),query.value(4).toString(),query.value(5).toString(),List);
            A->setStatus(true);
            A->ToUi(List);
        }
        else {
            FriendBox* A = new FriendBox("",query.value(1).toString(),query.value(4).toString(),query.value(5).toString(),List);
            A->setStatus(false);
            A->ToUi(List);
        }
    }
}
void FriendManager::LoadFriend (QListWidget* list,QString Name,bool ifonline)
{
    for (int i = 0; i < list->count(); i++) {
        QListWidgetItem* item = list->item(i);
        FriendBox * myWidget = qobject_cast<FriendBox *>(list->itemWidget(item));
        if (myWidget && myWidget->FriendName->text() == Name){
            if(ifonline)
            {
                myWidget->FriendStatus->setText("在线");
                myWidget->setStatus(true);
            }
            else
            {
                myWidget->FriendStatus->setText("离线");
                myWidget->setStatus(false);
            }
        }
    }
}
void FriendManager::ADDnewMessage(QListWidget* &list,QString Name)
{
    for (int i = 0; i < list->count(); i++) {
        QListWidgetItem* item = list->item(i);
        FriendBox * myWidget = qobject_cast<FriendBox *>(list->itemWidget(item));
        if (myWidget && myWidget->FriendName->text() == Name){
                int p = 1;
                if(!myWidget->NewMessage->text().isEmpty()) p = myWidget->NewMessage->text().toInt()+1;
                myWidget->NewMessage->setText(QString::number(p));
                myWidget->NewMassage(true);
        }
    }
}
