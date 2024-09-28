#include "thread.h"

ThreadLogin::ThreadLogin(QObject *parent) : QThread(parent)
{

}

void ThreadLogin::rev(QString s1, QString s2)
{
    ID = s1;
    Password = s2;
}

void ThreadLogin::run()
{
    DataBaseManager* B = new DataBaseManager();
    QString CheckResult = B->CheckIDandPassword(ID,Password);
    delete B;
    QString LoginResult;
    if (CheckResult == "账号和密码正确")
    {
        Connection* C = new Connection();
        C->ConnectToServer();
        if(C->ServerStatus()) LoginResult = "登录成功";
        else LoginResult = "无法连接至服务器";
        delete C;
    }
    else LoginResult = CheckResult;
    emit sendResult(LoginResult);
}

ThreadAI::ThreadAI(QObject *parent) : QThread(parent)
{

}
void ThreadAI::rev(QString s1)
{
    Message = s1;
}
void ThreadAI::run()
{
    QString Result;
    Result = AI::chatReply(Message);
    emit sendResult(Result);
}
