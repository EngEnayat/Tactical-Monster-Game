#include "second.h"
#include "ui_second.h"
#include "gallery.h"
second::second(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::second)
{
    ui->setupUi(this);
}

second::~second()
{
    delete ui;
}

void second::on_pushButton_clicked()
{
    hide();
    Gallery *g = new Gallery();
    g->show();
}

