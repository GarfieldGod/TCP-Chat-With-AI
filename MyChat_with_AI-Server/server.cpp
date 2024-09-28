#include "server.h"
#include "ui_server.h"


Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    ui->lineEdit_port->setText("8899");
    server_rec = new QTcpServer(this);

    DataBaseManager::connectToDatabase();
    DataBaseManager::LoadAllUsers(ui->list_allusers);

    //有新连接
    connect(server_rec,&QTcpServer::newConnection,this,[=](){
        QTcpSocket* tcp = server_rec->nextPendingConnection();
        //读取消息
        connect(tcp,&QTcpSocket::readyRead,this,[=](){
            QByteArray data = tcp->readAll();
            QList<QByteArray> lines = data.split('\n');
            QStringList LatestMessageList;
            for (const QByteArray& line : lines) {
                LatestMessageList.append(line);
            }
            for(QString Message :LatestMessageList)
            {
                qDebug()<<"服务器收到消息："<<Message;
                MessageProcess(tcp,Message);
            }

            //old:
            //QString MessageData = QString::fromUtf8(tcp->readAll());
            //qDebug()<<"服务器收到消息："<<MessageData;
            //MessageProcess(tcp,MessageData);
        });
        //用户断开链接
        connect(tcp,&QTcpSocket::disconnected,this,[=](){
            qDebug()<<"离线TCP为："<<UserManager::OnlineUser->value(tcp)<<":"<<tcp;
            QString Name = UserManager::OnlineUser->value(tcp);
            UserManager::Outlist(ui->list_onlineusers,1,Name);
            QString Time = QDateTime::currentDateTime().toString("yyyy年MM月dd日HH:mm:ss");
            UserManager::ChangeStatus(ui->list_allusers,Name,"离线","black");
            ui->message_rec->append(Name + " is offline");
            UserManager::OnlineTcp->remove(Name);
            UserManager::OnlineUser->remove(tcp);
            UserManager::UserStatusChangeToDatabase(Name,Time,0);
            UserManager::SendToAllOnlineUsers("Command ReLoadOfflineUsers " + Name);
            tcp->close();
            tcp->deleteLater();
        });
    });
}

Server::~Server()
{
    delete ui;
}

void Server::on_button_port_clicked()
{
    unsigned short port = ui->lineEdit_port->text().toUShort();
    server_rec->listen(QHostAddress::Any,port);
    ui->button_port->setEnabled(false);
}
//信息处理
void Server::MessageProcess(QTcpSocket* tcp,QString MessageData)
{
    QHostAddress userAddress = tcp->peerAddress();
    QString MessageClass = MessageData.section(' ', 0, 0);
    if(MessageClass == "LoginSucceed")
    {
        QString Name = MessageData.section(' ', 1, 1);
        UserManager::OnlineTcp->insert(Name,tcp);
        UserManager::OnlineUser->insert(tcp,Name);
        OfflineMessage::OfflineSend(Name);
        QString Time = MessageData.section(' ', 2, 2);
        UserManager::ChangeStatus(ui->list_allusers,Name,"在线","green");
        ui->message_rec->append(Name + " is online");
        UserManager::UserStatusChangeToDatabase(Name,Time,1);
        myrow* A = new myrow(Name,Time,userAddress.toString(),ui->list_onlineusers);
        A->ToUi(ui->list_onlineusers);
        UserManager::SendToAllOnlineUsers("Command ReLoadOnlineUsers " + Name);
    }
    else if(MessageClass == "Message")
    {
        ui->message_rec->append(MessageData);
        QString SENDname = MessageData.section(' ', 1, 1);
        QString RECname = MessageData.section(' ', 2, 2);
        QString SendTime = MessageData.section(' ', 3,3);
        QString content = MessageData.section(' ', 4);
        QString send = "Message "+SENDname+" "+SendTime+" "+content;
        if (UserManager::OnlineTcp->contains(RECname)) {
            qDebug()<<"转发消息:"<<send;
            UserManager::OnlineTcp->value(RECname)->write(send.toUtf8());
        }
        else
        {
            OfflineMessage::OfflineRead(MessageData);
            tcp->write("Error 对方不在线，将在上线后接收到该消息");
        }
    }
}
