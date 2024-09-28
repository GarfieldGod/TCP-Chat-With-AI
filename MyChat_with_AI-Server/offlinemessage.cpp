#include "offlinemessage.h"

OfflineMessage::OfflineMessage()
{

}

void OfflineMessage::OfflineRead(QString p)
{
    QString Sender = p.section(" ",1,1);
    QString Rec = p.section(" ",2,2);
    QString Time = p.section(" ",3,3);
    QString Content = p.section(" ",4);
    QDir dir;
    if (!dir.exists("OfflineMessage/")) {
       qDebug()<<"创建目录";
       dir.mkpath("OfflineMessage/");
    }
    QString filePath = "OfflineMessage/" + Rec + ".txt";
    QFile file(filePath);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << p << endl;
            file.close();
            qDebug() << "已创建：" << filePath;
         }
        else qDebug() << "文件创建失败:" << filePath;
    }
    else
    {
        if (file.open(QIODevice::Append)) {
            QTextStream out(&file);
            out << p << endl;
            file.close();
        }
    }
}

void OfflineMessage::OfflineSend(QString Name)
{
    QStringList result;
    qDebug()<<"读取聊天记录";
    QString filePath = "OfflineMessage/" + Name + ".txt";
    QFile file(filePath);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "读文件成功" << filePath;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                result.append(line);
            }
            file.close();
            file.remove();
        }
        else qDebug() << "读文件失败" << filePath;
    }
    else qDebug() << "无聊天记录" << filePath;
    for(QString MessageData:result)
    {
        QString SENDname = MessageData.section(' ', 1, 1);
        QString RECname = MessageData.section(' ', 2, 2);
        QString SendTime = MessageData.section(' ', 3,3);
        QString content = MessageData.section(' ', 4);
        QString send = "Message "+SENDname+" "+SendTime+" "+content;
        if (UserManager::OnlineTcp->contains(RECname)) {
            qDebug()<<"转发离线消息:"<<send;
            UserManager::OnlineTcp->value(RECname)->write(send.toUtf8()+"\n");
        }
        else qDebug()<<"离线转发失败";
    }
}
