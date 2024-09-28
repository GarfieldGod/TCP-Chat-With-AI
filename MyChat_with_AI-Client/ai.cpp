#include "ai.h"
QString AI::AccessToken;
AI::AI()
{
    AccessToken = getAccessToken();
}

QString AI::getAccessToken() {
    QUrl url("https://aip.baidubce.com/oauth/2.0/token");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    request.setRawHeader("Accept", "application/QString");

    QString data = "grant_type=client_credentials&client_id=" + client_id+ "&client_secret=" + client_secret;

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, data.toUtf8());

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();
    return obj["access_token"].toString();
}
QString AI::chatReply(QString Message)
{
    Message.replace("\n","。");
    qDebug()<<"AI收到："<<Message;
    QEventLoop eventLoop;
    QTimer delayTimer;
    delayTimer.setSingleShot(true);
    delayTimer.setInterval(2000);
    QObject::connect(&delayTimer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    if(Message == "谢芳琪") {
        delayTimer.start();
        eventLoop.exec();
        return "谢芳琪是世界上最可爱的人。";
    }
    if(Message.contains("世界上最可爱的人")) {
        delayTimer.start();
        eventLoop.exec();
        return "世界上最可爱的人是谢芳琪。";
    }

    //QString AccessToken = getAccessToken();
    //qDebug()<<AccessToken;
    QUrl url("https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/ernie_speed?access_token=" + AccessToken);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //QString Message = "进入闲聊模式";
    QByteArray Data = ("{\"messages\":[{\"role\":\"user\",\"content\":\" " + Message + " \"}]}").toUtf8();

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, Data);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray MessageData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(MessageData);
    QJsonObject jsonObj = doc.object();
    QJsonValue resultValue = jsonObj.value("result");
    QString resultString = resultValue.toString();
    qDebug() << "Result:" << resultString;
    return resultString;
}
