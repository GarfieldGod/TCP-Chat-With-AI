#ifndef MYUI_H
#define MYUI_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextBrowser>
#include <QScrollBar>
#include <QDebug>


class MyUI : public QWidget
{
    Q_OBJECT
public:
    explicit MyUI(QWidget *parent = nullptr);
    void ToUi(QListWidget* List,bool isclick);
};

class ChatBox : public MyUI
{
    Q_OBJECT
public:
    QTextBrowser* Content;
    explicit ChatBox(QWidget *parent = nullptr);
    ChatBox (QString time,QString speaker,QString content,int direction,QWidget *parent);
};

class FriendBox: public MyUI
{
    Q_OBJECT
public:
    QLabel* FriendName;
    QLabel* FriendStatus;
    QLabel* LastTimeOnline;
    QLabel* NewMessage;
    explicit FriendBox(QWidget *parent = nullptr);
    void setStatus(bool online);
    void NewMassage(bool news);
    void ToUi(QListWidget* List);
    FriendBox(QString newmessage,QString friendname,QString friendstatus,QString lasttimeonline,QWidget *parent);
};

class MessageBox: public MyUI
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = nullptr);
    MessageBox(QString time,QWidget *parent);
};

#endif // MYUI_H
