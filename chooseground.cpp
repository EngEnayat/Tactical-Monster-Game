#include "chooseground.h"
#include "ui_chooseground.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QGraphicsPolygonItem>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include "secondpage.h"
QString ChooseGround::PlayerTwo = "Khairullah";
QString ChooseGround::playerOne = "Mohammad";

ChooseGround::ChooseGround(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseGround)
{
    ui->setupUi(this);
    
    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);
    scene5 = new QGraphicsScene(this);
    scene6 = new QGraphicsScene(this);
    scene7 = new QGraphicsScene(this);
    scene8 = new QGraphicsScene(this);
    
    
    ui->graphicsView1->setScene(scene1);
    ui->graphicsView2->setScene(scene2);
    ui->graphicsView3->setScene(scene3);
    ui->graphicsView4->setScene(scene4);
    ui->graphicsView5->setScene(scene5);
    ui->graphicsView6->setScene(scene6);
    ui->graphicsView7->setScene(scene7);
    ui->graphicsView8->setScene(scene8);
    
    ui->graphicsView1->viewport()->installEventFilter(this);
    ui->graphicsView2->viewport()->installEventFilter(this);
    ui->graphicsView3->viewport()->installEventFilter(this);
    ui->graphicsView4->viewport()->installEventFilter(this);
    ui->graphicsView5->viewport()->installEventFilter(this);
    ui->graphicsView6->viewport()->installEventFilter(this);
    ui->graphicsView7->viewport()->installEventFilter(this);
    ui->graphicsView8->viewport()->installEventFilter(this);
    
    
    loadHexGrid(":/grids/grid1.txt", scene1, ui->graphicsView1);
    loadHexGrid(":/grids/grid2.txt", scene2, ui->graphicsView2);
    loadHexGrid(":/grids/grid3.txt", scene3, ui->graphicsView3);
    loadHexGrid(":/grids/grid4.txt", scene4, ui->graphicsView4);
    loadHexGrid(":/grids/grid5.txt", scene5, ui->graphicsView5);
    loadHexGrid(":/grids/grid6.txt", scene6, ui->graphicsView6);
    loadHexGrid(":/grids/grid7.txt", scene7, ui->graphicsView7);
    loadHexGrid(":/grids/grid8.txt", scene8, ui->graphicsView8);
    
    
    //set good css style for the button
    
    ui->GoToGalleryButton->setText("Select");
    ui->GoToGalleryButton->setFont(QFont("Segoe UI", 14, QFont::Bold));
    ui->GoToGalleryButton->setFixedSize(200, 60);
    
    ui->GoToGalleryButton->setStyleSheet(
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
    
    
    
    
    
    
    
    // Set a nice background for the main window
    this->setStyleSheet(
        "Splash {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a1a2e, stop:1 #16213e);"
        "}"
        );
    
    
}


bool ChooseGround::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QGraphicsView* clickedView = nullptr;
        
        if (obj == ui->graphicsView1->viewport())
        {
            clickedView = ui->graphicsView1;
            selectedMapName = ":/grids/grid1.txt";
        }
        else if (obj == ui->graphicsView2->viewport())
        {
            
            clickedView = ui->graphicsView2;
            selectedMapName = ":/grids/grid2.txt";
        }
        else if (obj == ui->graphicsView3->viewport())
        {
            
            clickedView = ui->graphicsView3;
            selectedMapName = ":/grids/grid3.txt";
        }
        else if (obj == ui->graphicsView4->viewport())
        {
            
            clickedView = ui->graphicsView4;
            selectedMapName = ":/grids/grid4.txt";
        }
        else if (obj == ui->graphicsView5->viewport())
        {
            
            clickedView = ui->graphicsView5;
            selectedMapName = ":/grids/grid5.txt";
        }
        
        else if (obj == ui->graphicsView6->viewport())
        {
            
            clickedView = ui->graphicsView6;
            selectedMapName = ":/grids/grid6.txt";
        }
        
        else if (obj == ui->graphicsView7->viewport())
        {
            
            clickedView = ui->graphicsView7;
            selectedMapName = ":/grids/grid7.txt";
        }
        else if (obj == ui->graphicsView8->viewport())
        {
            
            clickedView = ui->graphicsView8;
            selectedMapName = ":/grids/grid8.txt";
        }
        if (clickedView) {
            if (selectedView) {
                // حذف استایل قبلی از ویوی انتخاب‌شده قبلی
                selectedView->setStyleSheet("");
            }
            
            // تنظیم استایل روی ویوی جدید
            clickedView->setStyleSheet("border: 3px solid red;");
            selectedView = clickedView;
            
            qDebug() << "Selected view changed.";
        }
        
        return true;
    }
    
    return QWidget::eventFilter(obj, event);
}






void ChooseGround::loadHexGrid(const QString& filePath, QGraphicsScene* scene, QGraphicsView *view)
{
    scene->clear();
    
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return;
    }
    
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines << in.readLine();
    }
    file.close();
    
    for (int row = 0; row < lines.size()-1; row++) {
        const QString &line = lines[row];
        for (int col = 0; col < line.length()-1; ) {
            if (line[col] == '/') {
                QChar ch = line[col+1];
                if (ch == '\\' || ch == '_' || ch == '|') {
                    continue;
                }
                
                qreal x = (col / 6.0) * hexWidth * 1.5;
                qreal y = row * hexHeight * 0.5;
                
                createHexagon(x, y, ch, scene);
                col += 5;
            }
            else {
                col++;
            }
        }
    }
    
    if (!scene->items().empty()) {
        view->fitInView(scene->itemsBoundingRect().adjusted(-20, -20, 20, 20),
                        Qt::KeepAspectRatio);
    }
    view->scale(6,6);
}

QString ChooseGround::selectedMapName = "";

void ChooseGround::setSelectedMap(const QString &name)
{
    selectedMapName = name;
}

QString ChooseGround::getSelectedMap()
{
    return selectedMapName;
}




void ChooseGround::createHexagon(qreal x, qreal y, QChar ch, QGraphicsScene *scene)
{
    QPolygonF hexagon;
    hexagon << QPointF(hexWidth*0.25, 0)
            << QPointF(hexWidth*0.75, 0)
            << QPointF(hexWidth, hexHeight*0.5)
            << QPointF(hexWidth*0.75, hexHeight)
            << QPointF(hexWidth*0.25, hexHeight)
            << QPointF(0, hexHeight*0.5);
    
    QGraphicsPolygonItem *hexItem = new QGraphicsPolygonItem(hexagon);
    hexItem->setPos(x, y);
    
    if (ch == '1') {
        hexItem->setBrush(QColor(100, 255, 100));
    } else if (ch == '2') {
        hexItem->setBrush(QColor(255, 255, 100));
    } else if (ch == '#') {
        hexItem->setBrush(QColor(100, 100, 255)); // Blue
    } else if (ch == '~') {
        hexItem->setBrush(QColor(255, 150, 200)); // Pink
    } else {
        hexItem->setBrush(Qt::white); // Empty
    }
    
    hexItem->setPen(QPen(Qt::black, 1));
    scene->addItem(hexItem);
}

ChooseGround::~ChooseGround()
{
    delete ui;
}

void ChooseGround::on_GoToGalleryButton_clicked()
{
    qDebug()<<"On GoToGalleryButton Clicked!\n";
    this->hide();
    // AgentPage.show
    
    backtoSecondPage.show();
    
    
}

