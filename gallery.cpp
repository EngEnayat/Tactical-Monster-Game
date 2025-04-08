#include "gallery.h"
#include "ui_gallery.h"
#include "widget.h"
Gallery::Gallery(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gallery)
{
    ui->setupUi(this);
}

Gallery::~Gallery()
{
    delete ui;
}

void Gallery::on_pushButton_clicked()
{
    hide();
    Widget *w = new Widget();
    w->on_pushButton_clicked();
}

