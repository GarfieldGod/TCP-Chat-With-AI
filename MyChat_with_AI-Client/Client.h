#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QString>
#include <QtDebug>
#include <QTimer>
#include <QMovie>
#include <QDockWidget>
#include <QFormLayout>
#include <QHBoxLayout>

#include "mainui.h"
#include "connection.h"
#include "databasemanager.h"

#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();
    QString Style;

signals:
    void LoginThreadSend(QString s1,QString s2);
private:
    void write(QString ID,QString Password);
    void read(QLineEdit* ID,QLineEdit* Password);
    QDockWidget* registration;
    Ui::Client *ui;
    void CheckLogin(QString LoginResult);
};

class Register : public QDockWidget
{
public:
    Register(QWidget *parent = nullptr);
    QLabel* Message;
    QLineEdit* usernameEdit;
    QLineEdit* accountEdit;
    QLineEdit* passwordEdit;
    QString CheckRegister(QString username,QString account,QString password);
};
#endif // CLIENT_H
