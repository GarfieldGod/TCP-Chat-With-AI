#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>
#include <QMovie>
#include <QDockWidget>

#include "connection.h"
#include "chathistory.h"
#include "friendmanager.h"
#include "myui.h"
#include "thread.h"

#include "ai.h"

namespace Ui {
class MainUI;
}

class MainUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainUI(QWidget *parent = nullptr,QString UID = NULL);
    ~MainUI();
private slots:
    void on_button_sendmessage_clicked();
signals:
    void ChatAI(QString s1);
private:
    Ui::MainUI *ui;
    QString QssStyle;
    void MessageProcess(QString Message);
    void StatusChange(QLabel* Status,bool online);
    Connection* TcpConnect;
};

class Info : public QDockWidget
{
public:
    Info(QWidget *parent = nullptr);

};
#endif // MAINUI_H
