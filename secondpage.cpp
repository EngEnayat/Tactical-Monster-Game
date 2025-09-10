#include "secondpage.h"
#include "ui_secondpage.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
// #include "widget.h"
#include <QInputDialog>
#include <QMessageBox>
#include "chooseground.h"
bool SecondPage::onNameButtonClicked = false;
bool SecondPage::NameButtonClicked = false;
QString SecondPage::player1Name = "";
QString SecondPage::player2Name = "";

SecondPage::SecondPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecondPage)
{
    ui->setupUi(this);
    // ui->startSecond();
    ui->label->setPixmap(QPixmap(":/SplashPictures/secondpageImage.png"));
    ui->label->setScaledContents(true);
    //style of the title
    ui->label->setStyleSheet("QLabel {"
                             "   color: #f8d347;"
                             "   font-size: 36px;"
                             "   font-weight: bold;"
                             "   margin-bottom: 20px;"
                             "}");
    
    
    //button style
    ui->Agents->setFixedSize(200, 60);
    ui->Agents->setStyleSheet(
        "QPushButton {"
        "   color: white;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff512f, stop:1 #dd2476);"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   border: 2px solid #ffffff;"
        // "   margin 100 0 60 10;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dd2476, stop:1 #ff512f);"
        "}"
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #cc1c66, stop:1 #ee4025);"
        "}"
        );
    ui->Agents->move(280, 750);
    // Add button animation
    QGraphicsDropShadowEffect *buttonShadow = new QGraphicsDropShadowEffect;
    buttonShadow->setBlurRadius(15);
    buttonShadow->setColor(QColor(221, 36, 118, 150));
    buttonShadow->setOffset(0, 5);
    ui->Agents->setGraphicsEffect(buttonShadow);
    
    // Pulse animation for the button
    QPropertyAnimation *pulseAnim = new QPropertyAnimation(ui->Agents, "geometry");
    pulseAnim->setDuration(1000);
    pulseAnim->setLoopCount(-1); // Infinite loop
    pulseAnim->setKeyValueAt(0, ui->Agents->geometry());
    pulseAnim->setKeyValueAt(0.5, ui->Agents->geometry().adjusted(-5, -5, 5, 5));
    pulseAnim->setKeyValueAt(1, ui->Agents->geometry());
    pulseAnim->start();
    
    
    
    
    
    ui->Agents->setText("Gallery");
    ui->Agents->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->Agents->setFixedSize(200, 60);
    
    ui->Agents->setStyleSheet(
        "QPushButton {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                   stop: 0 #2980b9, stop: 1 #6dd5fa);"
        "   border-radius: 15px;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "}"
        ""
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                   stop: 0 #2575fc, stop: 1 #6dd5fa);"
        "   padding: 9px;"
        "}"
        ""
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                   stop: 0 #1a5f9e, stop: 1 #3ca8cc);"
        "   padding: 11px;"
        "}"
        );
   
    
    // ui->getNameButton->setText("‫‪Game‬‬ ‫‪PVP‬‬ ‫‪Async‬‬ ‫‪an‬‬ ‫‪Start‬‬");
    ui->getNameButton->setText("Game PVP Async an Start");
    // ui->getNameButton->setFixedSize(200, 60);
    ui->getNameButton->setStyleSheet(
        "QPushButton {"
        "   color: white;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff512f, stop:1 #dd2476);"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   border: 2px solid #ffffff;"
        // "   margin 100 0 60 10;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dd2476, stop:1 #ff512f);"
        "}"
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #cc1c66, stop:1 #ee4025);"
        "}"
        );
    ui->getNameButton->move(720, 750);
    // Add button animation
    QGraphicsDropShadowEffect *buttonSh = new QGraphicsDropShadowEffect;
    buttonSh->setBlurRadius(15);
    buttonSh->setColor(QColor(221, 36, 118, 150));
    buttonSh->setOffset(0, 5);
    ui->getNameButton->setGraphicsEffect(buttonSh);
    
    // Pulse animation for the button
    QPropertyAnimation *pulseAni = new QPropertyAnimation(ui->getNameButton, "geometry");
    pulseAni->setDuration(1000);
    pulseAni->setLoopCount(-1); // Infinite loop
    pulseAni->setKeyValueAt(0, ui->getNameButton->geometry());
    pulseAni->setKeyValueAt(0.5, ui->getNameButton->geometry().adjusted(-5, -5, 5, 5));
    pulseAni->setKeyValueAt(1, ui->getNameButton->geometry());
    pulseAni->start();
    
    
    
    // Set a nice background for the main window
    this->setStyleSheet(
        "SecondPage {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a1a2e, stop:1 #16213e);"
        "}"
        );
    
    ui->getNameButton->setText("Get Players Name");
    ui->getNameButton->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->getNameButton->setFixedSize(200, 60);
    
    ui->getNameButton->setStyleSheet(
        "QPushButton {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                   stop: 0 #2980b9, stop: 1 #6dd5fa);"
        "   border-radius: 15px;"
        "   color: white;"
        "   padding: 10px;"
        "   border: none;"
        "}"
        ""
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                   stop: 0 #2575fc, stop: 1 #6dd5fa);"
        "   padding: 9px;"
        "}"
        ""
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                   stop: 0 #1a5f9e, stop: 1 #3ca8cc);"
        "   padding: 11px;"
        "}"
        );
    
    
}

void SecondPage::startSecond() {}

void SecondPage::savePlayer1Name(const QString &name1)
{
    player1Name = name1;
}

void SecondPage::savePlayer2Name(const QString &name2)
{
    player2Name  = name2;
}

QString SecondPage::getPlayer1Name() {
    return player1Name;
}

QString SecondPage::getPlayer2Name() {
    return player2Name;
}











SecondPage::~SecondPage()
{
    delete ui;
}

void SecondPage::on_Agents_clicked()
{
    if(SecondPage::onNameButtonClicked == false)
    {
        QMessageBox::warning(this,"player names are not selected","Please Select your player names");
        return;
    }
    else{
        
    
    qDebug()<<"On Agents clicked\n";
    this->hide();
    agentsPage.show();
    }
}


void SecondPage::on_getNameButton_clicked()
{
    if(SecondPage::NameButtonClicked == true)
    {
        QMessageBox::warning(this,"Select Player names","Names Are Stored!");
        return;
    }
    bool ok1, ok2;
    SecondPage::onNameButtonClicked = true;
    player1Name = QInputDialog::getText(this, tr("Player 1 Name"),
                                                tr("Enter name for Player 1:"), QLineEdit::Normal,
                                                "", &ok1);
    if (!ok1 || player1Name.trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Missing Name"), tr("Please enter a name for Player 1."));
        return;
    }
    
    player2Name = QInputDialog::getText(this, tr("Player 2 Name"),
                                                tr("Enter name for Player 2:"), QLineEdit::Normal,
                                                "", &ok2);
    if (!ok2 || player2Name.trimmed().isEmpty()) {
        QMessageBox::warning(this, tr("Missing Name"), tr("Please enter a name for Player 2."));
        return;
    }
    SecondPage::NameButtonClicked = true;
  
    qDebug() << "Player 1:" << player1Name;
    qDebug() << "Player 2:" << player2Name;
    
    
    ChooseGround *chooseMapPage = new ChooseGround();
    chooseMapPage->show();
    this->close();
    
}

