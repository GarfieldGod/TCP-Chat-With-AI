#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QDateTime>

#include "myui.h"
#include "databasemanager.h"
#include "usermanager.h"
#include  "offlinemessage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_button_port_clicked();

private:
    Ui::Server *ui;
    QTcpServer* server_rec;
    void MessageProcess(QTcpSocket* tcp,QString MessageData);
};
#endif // SERVER_H
