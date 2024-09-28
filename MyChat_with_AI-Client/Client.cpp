#include "Client.h"
#include "ui_Client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    //样式
    setWindowIcon(QIcon(":/Project/Resource/PICTURE/ico.png"));
    this->setFixedSize(500, 400);
    ui->Label_Loading->hide();
    QMovie* movie=new QMovie(":/Project/Resource/GIF/Loading.gif");
    movie->setScaledSize(QSize(30, 30));
    ui->Label_Loading->setMovie(movie);
    movie->start();

    //测试
    read(ui->Input_Account,ui->Input_Password);
    //读取样式表
    QFile styleFile(":/Project/Resource/CSS/Client.qss");
    styleFile.open(QFile::ReadOnly);
    Style = QLatin1String(styleFile.readAll());
    setStyleSheet(Style);
    //注册
    Register* reg = new Register(this);
    connect(ui->Button_Register,&QPushButton::clicked,this,[=](){
        reg->show();
    });
    //子线程：登录
    ThreadLogin* LoginThread = new ThreadLogin;
    connect(this,&Client::LoginThreadSend,LoginThread,&ThreadLogin::rev);
    connect(ui->Button_Login,&QPushButton::clicked,this,[=](){
        ui->Label_message->setProperty("class", "success");
        ui->Label_Loading->show();
        setStyleSheet(Style);
        ui->Label_message->setText("登陆中...");
        emit LoginThreadSend(ui->Input_Account->text(),ui->Input_Password->text());
        LoginThread->start();
    });
    connect(LoginThread,&ThreadLogin::sendResult,this,[=](QString Result){
        ui->Label_Loading->hide();
        CheckLogin(Result);
    });
}

Client::~Client()
{
    delete ui;
}

//检查登录结果
void Client::CheckLogin(QString LoginResult)
{
    ui->Label_message->setText(LoginResult);

    if(LoginResult == "登录成功")
    {
        MainUI* mainui = new MainUI(nullptr,ui->Input_Account->text());
        mainui->show();
        write(ui->Input_Account->text(),ui->Input_Password->text());
        QTimer::singleShot(100, [&]() {
            qDebug()<<"登录窗口关闭"<<endl;
            this->close();
        });
    }
    else
    {
        ui->Label_message->setProperty("class", "error");
        setStyleSheet(Style);
        ui->Label_message->update();
    }
}

Register::Register(QWidget *parent): QDockWidget(parent)
{       Message = new QLabel("欢迎注册！");
        Message->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
        QVBoxLayout* layout = new QVBoxLayout(this);

        usernameEdit = new QLineEdit();
        accountEdit = new QLineEdit();
        passwordEdit = new QLineEdit();

        usernameEdit->setMinimumHeight(40);
        accountEdit->setMinimumHeight(40);
        passwordEdit->setMinimumHeight(40);
        QPushButton* Button = new QPushButton("注册");

        QLabel* username = new QLabel("昵称：");
        QLabel* account = new QLabel("用户名：");
        QLabel* password = new QLabel("密码：");

        layout->addWidget(Message);
        layout->addWidget(username);
        layout->addWidget(usernameEdit);
        layout->addWidget(account);
        layout->addWidget(accountEdit);
        layout->addWidget(password);
        layout->addWidget(passwordEdit);
        layout->addWidget(Button);

        QWidget* A = new QWidget();
        A->setLayout(layout);
        this->setWidget(A);
        this->setWindowTitle("注册");
        this->setFixedSize(300, 300);
        this->setFloating(true);
        this->hide();
            connect(Button,&QPushButton::clicked,this,[&](){
                DataBaseManager* B = new DataBaseManager();
                QString CheckResult = B->Register(usernameEdit->text(),accountEdit->text(),passwordEdit->text());
                delete B;
                QMessageBox::information(nullptr, "消息",CheckResult);
            });
}

void Client::write(QString ID,QString Password)
{
    QDir dir;
    if (!dir.exists("userdata")) {
       if(!dir.mkpath("userdata")) qDebug()<<"目录创建失败";
       else qDebug()<<"创建目录";
    }
    QString filePath = "userdata/Client.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << ID << endl;
        out << Password << endl;
        file.close();
    }
}
void Client::read(QLineEdit* ID,QLineEdit* Password)
{
    QString filePath = "userdata/Client.txt";
    QFile file(filePath);
    if (!file.exists()) return;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        ID->setText(in.readLine());
        Password->setText(in.readLine());
        file.close();
    }
}
