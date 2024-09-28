#ifndef CONNECTION_H
#define CONNECTION_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QDateTime>

class Connection: public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection();
    static QString UserID;
    static QString LatestMessage;
    static QStringList LatestMessageList;
    QTcpSocket* client_connect;
    bool ServerStatus();
    void ConnectToServer();
    void SendMessage(QString MessageData);
public slots:
private:
    QString SERVER_IP;
    unsigned short SERVER_PORT;

};

#endif // CONNECTION_H
