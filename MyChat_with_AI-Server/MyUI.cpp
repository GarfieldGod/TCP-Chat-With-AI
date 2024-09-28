#include "myui.h"

MyUI::MyUI(QWidget *parent) : QWidget(parent)
{

}
void MyUI::ToUi(QListWidget* List)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(this->sizeHint());
    List->addItem(item);
    List->setItemWidget(item, this);
    List->scrollToItem(item, QAbstractItemView::PositionAtBottom);
}
myrow::myrow(const QString String1, const QString String2, const QString String3,QWidget* parent) : MyUI(parent)
{
    content1 = new QLabel(String1);
    content2 = new QLabel(String2);
    content3 = new QLabel(String3);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(content1);
    layout->addWidget(content2);
    layout->addWidget(content3);
    setLayout(layout);
}
