#include "mainui.h"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent,QString UID) :
    QMainWindow(parent),
    ui(new Ui::MainUI)
{
    ui->setupUi(this);
    ui->label_username->setText(UID);
    //样式
    setWindowIcon(QIcon(":/Project/Resource/PICTURE/ico.png"));
    this->setWindowTitle("GarfieldGod's Chat with AI");
    //头像
    QString imagePath = ":/Project/Resource/PICTURE/Avator.jpg";
    ui->label_avator->setPixmap(QPixmap(imagePath));
    //ui->label_avator->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_avator->setScaledContents(true);
    Info* myinfo = new Info(this);
    connect(ui->Button_info,&QPushButton::clicked,this,[=](){
        myinfo->show();
    });
    //读取样式表
    QFile styleFile(":/Project/Resource/CSS/MainUI.qss");
    styleFile.open(QFile::ReadOnly);
    QssStyle = QLatin1String(styleFile.readAll());
    setStyleSheet(QssStyle);
    //建立AI
    AI *chatbot = new AI;
    ui->label_aiload->hide();
    QMovie* movie=new QMovie(":/Project/Resource/GIF/Loading.gif");
    movie->setScaledSize(QSize(30, 30));
    ui->label_aiload->setMovie(movie);
    movie->start();
    //连接服务器和数据库
    TcpConnect = new Connection();
    TcpConnect->ConnectToServer();
    DataBaseManager* DataBse = new DataBaseManager();
    DataBse->connectToDatabase();
    //读取好友列表
    FriendManager::LoadFriend (ui->list_friends);
    //运行AI
    ThreadAI* AI = new ThreadAI;
    connect(this, &MainUI::ChatAI,AI,&ThreadAI::rev);
    connect(ui->list_message, &QListWidget::itemClicked,this,[=](){
        ui->text_ai->setText("AI正在理解这段话...");
        ui->label_aiload->show();
        QList<QListWidgetItem*> selected = ui->list_message->selectedItems();
        if (!selected.isEmpty()){
            QListWidgetItem* item = selected.first();
            ChatBox* customWidget = qobject_cast<ChatBox*>(ui->list_message->itemWidget(item));
            if (customWidget) {
                emit ChatAI(customWidget->Content->toPlainText());
            }
        }
        AI->start();
    });
    connect(AI,&ThreadAI::sendResult,this,[=](QString Result){
        ui->textBrowser_ai->setHtml(Result);
        ui->text_ai->setText("AI");
        ui->label_aiload->hide();
    });
    //选中好友时,改变聊天框标题
    connect(ui->list_friends, &QListWidget::itemSelectionChanged, this,[=](){
        QList<QListWidgetItem*> selected = ui->list_friends->selectedItems();
        if (!selected.isEmpty()){
            QListWidgetItem* item = selected.first();
            FriendBox* customWidget = qobject_cast<FriendBox*>(ui->list_friends->itemWidget(item));
            if (customWidget) {
                ui->label_sendname->setText(customWidget->FriendName->text());
                customWidget->NewMessage->clear();
                customWidget->NewMassage(false);
                this->setStyleSheet(QssStyle);
                ui->list_message->clear();
                ChatHistory::readHistory(ui->label_username->text(),ui->label_sendname->text(),ui->list_message);
            }
        }
    }
    );
    //收到消息时，处理信息
    connect(TcpConnect->client_connect,&QTcpSocket::readyRead,this,[=](){
        for(QString Message :Connection::LatestMessageList)
        {
            Message.replace("谢芳琪", "世界上最可爱的人");
            qDebug()<<"处理消息："<<Message;
            MessageProcess(Message);
        }
    });
    //连接时
    connect(TcpConnect->client_connect,&QTcpSocket::connected,this,[=](){
        StatusChange(ui->label_status,true);qDebug()<<"服务器连接成功"<<endl;
        TcpConnect->SendMessage("LoginSucceed " + UID + " " + QDateTime::currentDateTime().toString("yyyy年MM月dd日HH:mm:ss"));
    });
    //断开连接时
    connect(TcpConnect->client_connect,&QTcpSocket::disconnected,this,[=](){
        StatusChange(ui->label_status,false);qDebug()<<"服务器断开连接"<<endl;
        TcpConnect->SendMessage("LoginOut " + UID + " " + QDateTime::currentDateTime().toString("yyyy年MM月dd日HH:mm:ss"));
    });
}
MainUI::~MainUI()
{
    delete ui;
}
//点击发送按钮，发送消息
void MainUI::on_button_sendmessage_clicked()
{
    if(ui->input_messagebox->toPlainText().isEmpty()||ui->label_sendname->text().isEmpty())
    {
        qDebug()<<"消息或收信人为空";
        MessageBox* A = new MessageBox("消息或收信人为空",ui->list_message);
        A->ToUi(ui->list_message,false);
        return;
    }
    if(ui->label_username->text() != NULL){
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString currentDateTimeString = currentDateTime.toString("yyyy年MM月dd日HH:mm:ss");
        QString MessageData = "Message " + ui->label_username->text() + " " + ui->label_sendname->text() +" "+ currentDateTimeString +" "+ ui->input_messagebox->toPlainText().replace("\n","<br>");
        ChatBox* A = new ChatBox(currentDateTimeString,ui->label_username->text(),ui->input_messagebox->toPlainText().replace("\n","<br>"),0,ui->list_message);
        A->ToUi(ui->list_message,false);
        ChatHistory::writeHistory(ui->label_username->text(),"MineSend " + ui->label_sendname->text() + " "+ currentDateTimeString +" "+ ui->input_messagebox->toPlainText().replace("\n","<br>"));
        ui->input_messagebox->clear();
        TcpConnect->SendMessage(MessageData);
    }
    else qDebug()<<"用户名校验失败";
}
//改变在线状态
void MainUI::StatusChange(QLabel* Status,bool online)
{
    if(online)
    {Status->setProperty("ID","Label_Status_Online");Status->setText("在线");}
    else
    {Status->setProperty("ID","Label_Status_Offline");Status->setText("离线");}
}
//消息处理
void MainUI::MessageProcess(QString Message)
{
    QString MessageClass = Message.section(' ', 0, 0);
    if(MessageClass == "LoginReply")
    {
    }
    else if(MessageClass == "Message")
    {
        QString Sender = Message.section(' ', 1, 1);
        QString sendTime = Message.section(' ', 2, 2);
        QString Content = Message.section(' ', 3);
        qDebug()<<Content;
        if(Sender == ui->label_sendname->text())
        {
            ChatBox* A = new ChatBox(sendTime,Sender,Content,1,ui->list_message);
            A->ToUi(ui->list_message,true);
        }
        else {FriendManager::ADDnewMessage(ui->list_friends,Sender);setStyleSheet(QssStyle);}
        ChatHistory::writeHistory(ui->label_username->text(),Message);
    }
    else if(MessageClass == "Error")
    {
        MessageBox* A = new MessageBox(Message.section(' ', 1),ui->list_message);
        A->ToUi(ui->list_message,false);
    }
    else if(MessageClass == "Command")
    {
        QString Content = Message.section(' ', 1, 1);
        if(Content == "ReLoadOnlineUsers"){
            FriendManager::LoadFriend (ui->list_friends,Message.section(' ', 2,2),true);
            this->setStyleSheet(QssStyle);
        }
        else if(Content == "ReLoadOfflineUsers"){
            FriendManager::LoadFriend (ui->list_friends,Message.section(' ', 2,2),false);
            this->setStyleSheet(QssStyle);
        }
    }
}

Info::Info(QWidget *parent): QDockWidget(parent)
{
    QLabel* title = new QLabel("GarfieldGod's Chat with AI");
    QLabel* me = new QLabel("作者：GarfieldGod");
    QLabel* date = new QLabel("制作日期：2024年7月");
    QLabel* page = new QLabel("个人主页：garfieldgod.cn");
    QLabel* welcome = new QLabel("\n  欢迎使用GarfieldGod制作的软件，点击用户列表中的用户，在右方输入内容即可向指定用户发送内容！\n\n  该软件可以实现离线消息转发、消息记录等功能\n\n  另外，点击接收到的消息，可由AI帮助解析！\n");
    welcome->setWordWrap(true);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(me);
    layout->addWidget(date);
    layout->addWidget(page);
    layout->addWidget(welcome);
    QWidget* A = new QWidget();
    A->setLayout(layout);
    this->setWidget(A);
    this->setWindowTitle("关于");
    this->setFixedSize(300, 300);
    this->setFloating(true);
    this->hide();
}
