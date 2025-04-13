#include "widget.h"
#include "./ui_widget.h"
#include <QTabBar>
#include <QMessageBox>
#include <QLineEdit>
#include <QString>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);// for first tab
    ui->tabWidget->tabBar()->hide();// for hiding the tabs

}

Widget::~Widget()
{
    delete ui;

}

void Widget::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}




void Widget::on_pushButton_3_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}


void Widget::on_pushButton_4_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void Widget::on_StartGameButton_clicked()
{
    QString name1 = ui->lineEdit_player1->text();
    QString name2 = ui->lineEdit_player2->text();

    if (name1.isEmpty() || name2.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter both player names!");
    } else {
        // Start game or show next tab...
        ui->tabWidget->setCurrentIndex(4); // If you have a next tab
    }
}

