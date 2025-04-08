#include "widget.h"
#include "./ui_widget.h"
#include "second.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    hide();
    second *s = new second();
    s->show();

}

