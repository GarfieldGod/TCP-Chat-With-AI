#ifndef MYUI_H
#define MYUI_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QListWidget>
#include <QDebug>
class MyUI : public QWidget
{
    Q_OBJECT
public:
    explicit MyUI(QWidget *parent = nullptr);
    void ToUi(QListWidget* List);
};

class myrow : public MyUI
{
    Q_OBJECT
public:
    QLabel* content1;
    QLabel* content2;
    QLabel* content3;
    myrow(const QString String1, const QString String2, const QString String3,QWidget* parent);
};
#endif // MYUI_H
