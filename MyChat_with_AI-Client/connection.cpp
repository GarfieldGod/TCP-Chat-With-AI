#include "connection.h"

QString Connection::LatestMessage = "";
QStringList Connection::LatestMessageList = {};

Connection::Connection(QObject *parent) : QObject(parent)
{
    SERVER_IP = "8.137.17.253";
    //SERVER_IP = "127.0.0.1";
    SERVER_PORT = 8899;

    client_connect = new QTcpSocket(this);
    //总台接收消息
    connect(client_connect,&QTcpSocket::readyRead,this,[=](){
        QByteArray data = Connection::client_connect->readAll();
        QList<QByteArray> lines = data.split('\n');
        LatestMessageList.clear();
        for (const QByteArray& line : lines) {
            LatestMessageList.append(line);
        }
        LatestMessage = QString::fromUtf8(data).replace("谢芳琪", "世界上最可爱的人");
        qDebug()<<"收到消息："<<LatestMessage;
    });
}
Connection::~Connection()
{
    delete client_connect;
}
void Connection::ConnectToServer()
{
    client_connect->connectToHost(QHostAddress(SERVER_IP),SERVER_PORT);
}
bool Connection::ServerStatus()
{
    if (client_connect->waitForConnected(5000))
        {client_connect->close();return true;}
    else
        {client_connect->close();return false;}
}
void Connection::SendMessage(QString MessageData)
{
    client_connect->write(MessageData.toUtf8());
}

