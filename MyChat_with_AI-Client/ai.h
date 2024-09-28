#ifndef AI_H
#define AI_H

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QDebug>
#include <QTimer>

class AI
{
public:
    static QString AccessToken;
    AI();
    static QString chatReply(QString Message);
private:
    const QString client_id = "RV55dGmtLTtGShXSGnJeluf7";
    const QString client_secret = "jOdvbf7MSlpWEm0jjpgYGggR3j5S7QrQ";
    QString getAccessToken();
};

#endif // AI_H
