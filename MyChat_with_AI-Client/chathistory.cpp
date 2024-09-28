#include "chathistory.h"

ChatHistory::ChatHistory()
{

}
//收到聊天消息后写入到文件中
void ChatHistory::writeHistory(QString Name,QString p)
{
    QDir dir;
    if (!dir.exists("Chathistory/" + Name)) {
       if(!dir.mkpath("Chathistory/" + Name)) qDebug()<<"目录创建失败";
       else qDebug()<<"创建目录";
    }
    //else qDebug()<<"目录已存在";
    QString sender = p.section(' ', 1, 1);
    QString filePath = "Chathistory/" + Name +"/"+ sender + ".txt";
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
//从文件中读取消息记录
void ChatHistory::readHistory(QString Name,QString UserName,QListWidget* parent)
{
    qDebug()<<"读取聊天记录";
    QStringList result;
    QString filePath = "Chathistory/" + Name +"/"+ UserName + ".txt";
    QFile file(filePath);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                result.append(line);
                qDebug() << "读取:" << line;
            }
            file.close();
        }
        else qDebug() << "读文件失败" << filePath;
    }
    else qDebug() << "无聊天记录" << filePath;
    for(QString line:result)
    {
        //qDebug()<<line;
        int direction = 0;
        if(line.section(" ",0,0) == "Message") direction = 1;
        ChatBox* A = new ChatBox(line.section(" ",2,2),line.section(" ",1,1),line.section(" ",3),direction,parent);
        if(direction) A->ToUi(parent,true);
        else A->ToUi(parent,false);
    }
}
