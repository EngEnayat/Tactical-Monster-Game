#include "gallery.h"
#include "ui_gallery.h"

Gallery::Gallery(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Gallery)
{
    ui->setupUi(this);
}

Gallery::~Gallery()
{
    delete ui;
}
