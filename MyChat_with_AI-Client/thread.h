#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QDebug>

#include <databasemanager.h>
#include <connection.h>
#include <ai.h>

class ThreadLogin : public QThread
{
    Q_OBJECT
public:
    explicit ThreadLogin(QObject *parent = nullptr);
    void rev(QString s1,QString s2);
protected:
    void run() override;
private:
    QString ID,Password;
signals:
    void sendResult(QString result);

};

class ThreadAI : public QThread
{
    Q_OBJECT
public:
    explicit ThreadAI(QObject *parent = nullptr);
    void rev(QString s1);
protected:
    void run() override;
private:
    QString Message;
signals:
    void sendResult(QString result);

};

#endif // THREAD_H
