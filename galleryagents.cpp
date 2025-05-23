#include "galleryagents.h"
#include "ui_galleryagents.h"
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QMessageBox>
#include "widget.h"

int GalleryAgents::agentCount = 0;
GalleryAgents::GalleryAgents(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GalleryAgents)
{
    ui->setupUi(this);
    ui->label->setText("GROUNDED AGENTS");
    ui->label_2->setText("WATER WALKING AGENTS");
    ui->label_3->setText("FLYING AGENTS");
    ui->label_4->setText("FLOATING AGENTS");
    QString s =
        (
            "QLabel {"
            "   background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #4e54c8, stop:1 #8f94fb);"
            "   border-radius: 10px;"
            "   color: white;"
            "   font: bold 16px 'Segoe UI', sans-serif;"
            "   padding: 10px;"
            "   min-width: 120px;"
            "   text-align: center;"
            "   border: 1px solid #333;"
            "   box-shadow: 3px 3px 5px rgba(0,0,0,0.3);"
            "}"
                 );
    ui->label->setStyleSheet(s);
    ui->label_2->setStyleSheet(s);
    ui->label_3->setStyleSheet(s);
    ui->label_4->setStyleSheet(s);


    // for start button

    ui->StartButton->setText("Start Game");
    ui->StartButton->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->StartButton->setFixedSize(200, 60);

    ui->StartButton->setStyleSheet(
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

    // end of graphic for start button

    // Grounded agents
    this->setButtonImage(ui->Kabu, ":/preAgent/Agents/Kabu.webp");
    this->setButtonImage(ui->Boi, ":/preAgent/Agents/Boi.webp");
    this->setButtonImage(ui->Salih, ":/preAgent/Agents/Salih.webp");
    this->setButtonImage(ui->SirLamorak, ":/preAgent/Agents/Lamorak.webp");
    this->setButtonImage(ui->Elsa, ":/preAgent/Agents/Elsa.webp");
    this->setButtonImage(ui->Khan, ":/preAgent/Agents/Khan.webp");
    this->setButtonImage(ui->Rajakal, ":/preAgent/Agents/Rajakal.webp");
    this->setButtonImage(ui->Tusk, ":/preAgent/Agents/Tusk.webp");
    this->setButtonImage(ui->Eloi, ":/preAgent/Agents/Eloi (1).webp");
    this->setButtonImage(ui->SirFillip, ":/preAgent/Agents/Sir philiph.webp");
    this->setButtonImage(ui->Kanar, ":/preAgent/Agents/Kanar.webp");
    this->setButtonImage(ui->Karissa, ":/preAgent/Agents/Karissa.webp");
    this->setButtonImage(ui->Frust, ":/preAgent/Agents/Frost.webp");

    // WATER WALKING AGENTS
    this->setButtonImage(ui->billy, ":/preAgent/Agents/Billy.webp");
    this->setButtonImage(ui->Reketon, ":/preAgent/Agents/Reketon.webp");
    this->setButtonImage(ui->Angus, ":/preAgent/Agents/Angus.webp");
    this->setButtonImage(ui->Duraham, ":/preAgent/Agents/Duraham.webp");
    this->setButtonImage(ui->ColonelBaba, ":/preAgent/Agents/Colonel_baba.webp");
    this->setButtonImage(ui->Bunka, ":/preAgent/Agents/Bunka.webp");
    this->setButtonImage(ui->Sanka, ":/preAgent/Agents/Sanka.webp");
    this->setButtonImage(ui->Medusa, ":/preAgent/Agents/Medusa.webp");

    // Floating
    this->setButtonImage(ui->Sabrina, ":/preAgent/Agents/Sabrina.webp");
    this->setButtonImage(ui->Death, ":/preAgent/Agents/death.webp");

    // Flying
    this->setButtonImage(ui->Rambu, ":/preAgent/Agents/Rambo.webp");

    connect(ui->Kabu, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Grounded", 120, 1,"Kabu", ":/preAgent/Agents/Kabu.webp");
    });
    connect(ui->SirLamorak, &QPushButton::clicked,[=](){
        showProperties(320, 3, "Grounded",110, 1,"Sir Lamorak", ":/preAgent/Agents/Lamorak.webp");
    });
    connect(ui->Rajakal, &QPushButton::clicked,[=](){
        showProperties(320, 2, "Grounded",130, 1,"Rajakal", ":/preAgent/Agents/Rajakal.webp");
    });
    connect(ui->Salih, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Grounded",80, 1,"Salih", ":/preAgent/Agents/Salih.webp");
    });
    connect(ui->Khan, &QPushButton::clicked,[=](){
        showProperties(320, 2, "Grounded",90, 1,"Khan", ":/preAgent/Agents/Khan.webp");
    });
    connect(ui->Boi, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Grounded",100, 1,"Boi", ":/preAgent/Agents/Boi.webp");
    });
    connect(ui->Eloi, &QPushButton::clicked,[=](){
        showProperties(240, 2, "Grounded",100, 1,"Eloi", ":/preAgent/Agents/Eloi (1).webp");
    });
    connect(ui->Kanar, &QPushButton::clicked,[=](){
        showProperties(169, 2, "Grounded",100, 1,"Kanar", ":/preAgent/Agents/Kanar.webp");
    });
    connect(ui->Elsa, &QPushButton::clicked,[=](){
        showProperties(320, 2, "Grounded",140, 1,"Elsa", ":/preAgent/Agents/Elsa.webp");
    });
    connect(ui->Karissa, &QPushButton::clicked,[=](){
        showProperties(280, 2, "Grounded",80, 2,"Karissa", ":/preAgent/Agents/Karissa.webp");
    });
    connect(ui->SirFillip, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Grounded",100, 1,"Sir Philip", ":/preAgent/Agents/Sir philiph.webp");
    });
    connect(ui->Frust, &QPushButton::clicked,[=](){
        showProperties(260, 2, "Grounded",80, 2,"Frust", ":/preAgent/Agents/Frost.webp");
    });
    connect(ui->Tusk, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Grounded",100, 1,"Tusk", ":/preAgent/Agents/Tusk.webp");
    });

    // WATER WALKING AGENTS

    connect(ui->billy, &QPushButton::clicked,[=](){
        showProperties(320, 3, "Water Walking",90, 1,"Billy", ":/preAgent/Agents/Billy.webp");
    });
    connect(ui->Reketon, &QPushButton::clicked,[=](){
        showProperties(320, 2, "Water Walking",80, 2,"Reketon", ":/preAgent/Agents/Reketon.webp");
    });
    connect(ui->Angus, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Water Walking",100, 1,"Angus", ":/preAgent/Agents/Angus.webp");
    });
    connect(ui->Duraham, &QPushButton::clicked,[=](){
        showProperties(320, 2, "Water Walking",100, 2,"Duraham", ":/preAgent/Agents/Duraham.webp");
    });
    connect(ui->ColonelBaba, &QPushButton::clicked,[=](){
        showProperties(400, 2, "Water Walking",100, 1,"Colonel Baba", ":/preAgent/Agents/Colonel_baba.webp");
    });

    connect(ui->Medusa, &QPushButton::clicked,[=](){
        showProperties(320, 2, "Water Walking",90, 2,"Medusa", ":/preAgent/Agents/Medusa.webp");
    });
    connect(ui->Bunka, &QPushButton::clicked,[=](){
        showProperties(320, 3, "Water Walking",100, 1,"Bunka", ":/preAgent/Agents/Bunka.webp");
    });
    connect(ui->Sanka, &QPushButton::clicked,[=](){
        showProperties(320, 3, "Water Walking",100, 1,"Sanka", ":/preAgent/Agents/Sanka.webp");
    });


    // Floating

    connect(ui->Sabrina, &QPushButton::clicked,[=](){
        showProperties(320, 3, "Floating",100, 1,"Sabrina", ":/preAgent/Agents/Sabrina.webp");
    });
    connect(ui->Death, &QPushButton::clicked,[=](){
        showProperties(240, 2, "Floating",120, 2,"Death", ":/preAgent/Agents/death.webp");
    });


    // Flying

    connect(ui->Rambu, &QPushButton::clicked,[=](){
        showProperties(320, 3, "Flying",120, 1,"Rambu", ":/preAgent/Agents/Rambo.webp");
    });

}

GalleryAgents::~GalleryAgents()
{
    delete ui;
}


void GalleryAgents::setButtonImage(QPushButton* button, const QString& imagePath)
{
    button->setStyleSheet(QString(R"(
        QPushButton {
            border-image: url(%1) 0 0 0 0 stretch stretch;
            background-repeat: no-repeat;
            background-position: center;
        }
    )").arg(imagePath));
}


void GalleryAgents::on_Kabu_clicked()
{

}

void GalleryAgents::showProperties(int hp, int mobility, QString type, int Damage, int AttackRange, QString name, QString path)
{
    if(agentCount > 11)
    {
        QMessageBox msgBox;
        msgBox.setText("All Agents have selected.\n Click on start button to start");
        msgBox.exec();
        qDebug() << "Player one Selected Agents: ";
        for(QString &str : PlayerOneAgents)
        {
            qDebug() << str << "\n";
        }
        qDebug() << "Player two Selected Agents: ";
        for(QString &str : PlayerTwoAgents)
        {
            qDebug() << str << "\n";
        }
        return;
    }
    QDialog dialog(this);
    dialog.setWindowTitle("Agent Info");
    dialog.setFixedSize(500, 320);

    dialog.setStyleSheet(
        "QDialog {"
        "   background-color: #ffffff;"
        "   border-radius: 12px;"
        "}"
        "QLabel {"
        "   color: #2c2c2c;"
        "   font-family: 'Segoe UI';"
        "}"
        );

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    QHBoxLayout* contentLayout = new QHBoxLayout();

    QLabel* imageLabel = new QLabel();
    QPixmap pixmap(path);

    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imageLabel->setStyleSheet("border-radius: 8px; background-color: #f0f0f0;");
    } else {
        imageLabel->setText("Image not found");
        imageLabel->setStyleSheet("color: red; font-weight: bold;");
    }

    QString htmlText = QString(
                           "<b>Name:</b> %1<br/>"
                           "<b>Type:</b> %2<br/>"
                           "<b>HP:</b> %3<br/>"
                           "<b>Mobility:</b> %4<br/>"
                           "<b>Damage:</b> %5<br/>"
                           "<b>AttackRange:</b> %6"
                           ).arg(name)
                           .arg(type)
                           .arg(hp)
                           .arg(mobility)
                           .arg(Damage)
                           .arg(AttackRange);

    QLabel* textLabel = new QLabel(htmlText);
    textLabel->setFont(QFont("Segoe UI", 12));

    contentLayout->addWidget(imageLabel, 0, Qt::AlignTop);
    contentLayout->addWidget(textLabel, 1);

    // Buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton* chooseButton = buttonBox->addButton("Choose as Agent", QDialogButtonBox::AcceptRole);
    QPushButton* cancelButton = buttonBox->addButton("Cancel", QDialogButtonBox::RejectRole);

    // Style buttons
    chooseButton->setStyleSheet(
        "QPushButton {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4CAF50, stop: 1 #45a049);"
        "   color: white;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        );

    cancelButton->setStyleSheet(
        "QPushButton {"
        "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #f44336, stop: 1 #e57373);"
        "   color: white;"
        "   border-radius: 6px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #ef5350;"
        "}"
        );

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    QString playerWEl = "";
    if(agentCount <= 5) playerWEl = "Player ONE Choose your " + QString::number(agentCount + 1) + "th" + " agent";
    else if(agentCount > 5 ) playerWEl= "Player TWO Choose your " + QString::number(agentCount-4) + "th" + " agent";
    QLabel* headerLabel = new QLabel(playerWEl);
    headerLabel->setFont(QFont("Segoe UI", 14, QFont::Bold));
    headerLabel->setStyleSheet("color: #333; margin-bottom: 10px;");

    mainLayout->addWidget(headerLabel, 0, Qt::AlignLeft);
    mainLayout->addLayout(contentLayout);
    mainLayout->addWidget(buttonBox, 0, Qt::AlignBottom | Qt::AlignRight);

    int result = dialog.exec();

    if (result == QDialog::Accepted) {
        if(agentCount <=5)
        {       PlayerOneAgents.append(name);
                agentCount++;
        }
        else if(agentCount>5 && agentCount <= 11)
        {
            PlayerTwoAgents.append(name);
            agentCount++;;
        }
    } else {
        qDebug() << "User canceled.";
    }
}


void GalleryAgents::on_StartButton_clicked()
{
    // if(agentCount <=11)
    // {
    //     QMessageBox msgBox;
    //     msgBox.setText("PLEASE try after completion of selection");
    //     msgBox.exec();
    //     return;
    // }
    Widget *w = new Widget(PlayerOneAgents, PlayerTwoAgents);
    w->show();
    this->hide();
}

