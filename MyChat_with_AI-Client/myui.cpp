#include "myui.h"

MyUI::MyUI(QWidget *parent) : QWidget(parent)
{

}
void MyUI::ToUi(QListWidget* List,bool isclick)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(this->sizeHint());
    if(!isclick) item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    List->addItem(item);
    List->setItemWidget(item, this);
    List->scrollToItem(item, QAbstractItemView::PositionAtBottom);
}

ChatBox::ChatBox(QString time,QString speaker,QString content,int direction,QWidget *parent) : MyUI(parent)
{
    //content.replace("\t","<br>");
    QLabel* Time = new QLabel(time);
    Time->setFixedHeight(30);

    QLabel* Speaker = new QLabel(speaker);

    Content = new QTextBrowser();
    Content->setHtml(content);

    QWidget* mid = new QWidget;
    QWidget* left = new QWidget;
        left->setFixedWidth(150);
    QWidget* right = new QWidget;
        right->setFixedWidth(150);

    QWidget* box = new QWidget;
    QHBoxLayout* boxlayout = new QHBoxLayout;
    boxlayout->addWidget(left);
    boxlayout->addWidget(mid);
    boxlayout->addWidget(right);
    box->setLayout(boxlayout);
    //消息内容
    QVBoxLayout* Contentlayout = new QVBoxLayout;
    Contentlayout->addWidget(Content);
    mid->setLayout(Contentlayout);
    //消息来源方
    QSpacerItem* verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QVBoxLayout* speakerlayout = new QVBoxLayout;
    speakerlayout->addWidget(Speaker);
    speakerlayout->addItem(verticalSpacer);
    //判断消息来源
    switch (direction) {
    case 0:
        //右边
        Time->setAlignment(Qt::AlignCenter | Qt::AlignRight);
        Content->setAlignment(Qt::AlignTop | Qt::AlignRight);
        right->setLayout(speakerlayout);
        break;
    case 1:
        //左边消息
        Content->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        left->setLayout(speakerlayout);
        break;
    default:
        break;
    }
    Speaker->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    //应用样式表
    setProperty("ID", "Chatbox_Chatbox");
    box->setProperty("ID", "Chatbox_box");
    left->setProperty("ID", "Chatbox_left");
    right->setProperty("ID", "Chatbox_right");
    mid->setProperty("ID", "Chatbox_mid");
    Speaker->setProperty("ID", "Chatbox_Speaker");
    Time->setProperty("ID", "Chatbox_Time");
    Content->setProperty("ID", "Chatbox_Content");

    //最终盒：上时间-下盒
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(Time);
    layout->addWidget(box);
    setLayout(layout);

    boxlayout->setContentsMargins(0, 0, 0, 0);
    Contentlayout->setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);

    //将文档调整到合理的大小。
    Content->document()->adjustSize();
    int newheight = Content->document()->size().rheight();
    if (newheight != Content->height())
    {
        Content->setFixedHeight(newheight+5);
    }
}
MessageBox::MessageBox(QString Message,QWidget *parent) : MyUI(parent)
{
    QLabel* Content = new QLabel(Message);
    Content->setFixedHeight(16);
    Content->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    setProperty("ID", "MessageBox");
    Content->setProperty("ID", "MessageBox_Content");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(Content);
    setLayout(layout);
}
FriendBox::FriendBox(QString newmessage,QString friendname,QString friendstatus,QString lasttimeonline,QWidget *parent) : MyUI(parent)
{
    NewMessage = new QLabel(newmessage);
    FriendName = new QLabel(friendname);
    FriendStatus = new QLabel(friendstatus);
    LastTimeOnline = new QLabel(lasttimeonline);

    QHBoxLayout* Layout = new QHBoxLayout();
    Layout->addWidget(NewMessage);
    Layout->addWidget(FriendName);
    Layout->addWidget(FriendStatus);
    Layout->addWidget(LastTimeOnline);
    setLayout(Layout);
    NewMessage->setFixedSize(20,20);
    FriendName->setFixedSize(100,20);
    FriendStatus->setFixedSize(40,20);
    LastTimeOnline->setFixedSize(200,20);

    NewMessage->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
}
void FriendBox::ToUi(QListWidget* List)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(this->sizeHint());
    List->addItem(item);
    List->setItemWidget(item, this);
}
void FriendBox::setStatus(bool online)
{
    if(online)
    {
        this->setProperty("ID", "FriendBox_online");
        FriendName->setProperty("ID", "FriendBox_FriendName_online");
        FriendStatus->setProperty("ID", "FriendBox_FriendStatus_online");
        LastTimeOnline->setProperty("ID", "FriendBox_LastTimeOnline_online");
    }
    else
    {
        this->setProperty("ID", "FriendBox_offline");
        FriendName->setProperty("ID", "FriendBox_FriendName_offline");
        FriendStatus->setProperty("ID", "FriendBox_FriendStatus_offline");
        LastTimeOnline->setProperty("ID", "FriendBox_LastTimeOnline_offline");
    }
}
void FriendBox::NewMassage(bool news)
{
    if(news) NewMessage->setProperty("ID", "FriendBox_NewMessage_new");
    else NewMessage->setProperty("ID", "FriendBox_NewMessage_none");
}
