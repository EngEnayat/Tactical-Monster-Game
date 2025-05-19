#include "widget.h"
#include "./ui_widget.h"
<<<<<<< HEAD
#include <QFile>
#include <QGraphicsScene>
#include <QDebug>
#include "hexagonitems.h"
#include <QGraphicsWidget>
#include <qgraphicssceneevent.h>
#include <QTimer>
#include "hexagonagents.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QGraphicsItem>
=======
#include "second.h"
>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
<<<<<<< HEAD

    ui->setupUi(this);
    ui->agentOne->setMinimumWidth(150);
    ui->agentTwo->setMinimumWidth(150);

    this->setStyleSheet(
        "QLabel {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "      stop:0 rgba(30, 30, 30, 220),"
        "      stop:1 rgba(60, 60, 80, 240));"
        "  color: #FFD700;"  // Tactical gold
        "  font-size: 26px;"
        "  font-weight: 700;"
        "  font-family: 'Segoe UI', 'Orbitron', 'Arial';"
        "  border: 2px solid #FFD700;"
        "  border-radius: 14px;"
        "  padding: 10px 20px;"
        "  letter-spacing: 1px;"
        "}"
        );



    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->viewport()->setMouseTracking(true);
    ui->agentOne->viewport()->setMouseTracking(true);
    ui->agentOne->viewport()->installEventFilter(this);

    ui->agentTwo->viewport()->setMouseTracking(true);
    ui->agentTwo->viewport()->installEventFilter(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // this->setBackground();
    qDebug() << "Created";
    QFile file(":/grids/grid1.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QStringList lines;
        QTextStream in(&file);
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
                        col += 2;
                        continue;
                    }

                    qreal x = (col / 6.0) * hexWidth * 1.5;
                    qreal y = row * hexHeight * 0.5;
                    createHexagon(x, y, ch, row, col / 6);
                    col += 5;
                }
                else {
                    col++;
                }
            }
        }
    }


    this->LoadingAgents(ui->agentOne);
    this->LoadingAgents(ui->agentTwo);
    agentsTwo[6]->setVisible(true);
    agentsOne[6]->setVisible(true);
}

void Widget::createHexagon(qreal x, qreal y, QChar ch, int row, int col)
{
    QPolygonF hexagon;
    hexagon << QPointF(hexWidth*0.25, 0)
            << QPointF(hexWidth*0.75, 0)
            << QPointF(hexWidth, hexHeight*0.5)
            << QPointF(hexWidth*0.75, hexHeight)
            << QPointF(hexWidth*0.25, hexHeight)
            << QPointF(0, hexHeight*0.5);

    HexagonItems *hexItem = new HexagonItems(hexagon, row, col);
    hexItem->setPos(x, y);

    if (ch == '1') {
        hexItem->setProperties(1, false, '1');
        hexItem->setBrush(QColor(120,170,120));
    } else if (ch == '2') {
        hexItem->setProperties(2, false, '2');
        hexItem->setBrush(QColor(255, 255, 100));
    } else if (ch == '#') {
        hexItem->setProperties(0, true, '#');
        hexItem->setBrush(QColor(32, 107, 186));
    } else if (ch == '~') {
        hexItem->setProperties(0, true, '~');
        hexItem->setBrush(QColor(189, 40, 117));
    } else {
        hexItem->setBrush(Qt::white);
    }

    hexMap[{row, col}] = hexItem;

    hexItem->setPen(QPen(Qt::black, 1));
    scene->addItem(hexItem);
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    QGraphicsView* view = nullptr;

    if (obj == ui->graphicsView->viewport())
        view = ui->graphicsView;
    else if (obj == ui->agentOne->viewport())
        view = ui->agentOne;
    else if (obj == ui->agentTwo->viewport())
        view = ui->agentTwo;

    if (view) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = view->mapToScene(mouseEvent->pos());

            if (view == ui->graphicsView) {
                if (lastHoveredHex && lastHoveredHex != getHexagonAtPosition(scenePos)) {
                    lastHoveredHex->resetColor();
                    lastHoveredHex = nullptr;
                }

                HexagonItems* hex = getHexagonAtPosition(scenePos);
                if (hex && hex != lastHoveredHex) {
                    if (hex->PlayerOwn() == 1)
                    {
                        hex->setScale(1.05);
                        hex->setBrush(QColor(44, 118, 41));
                    }
                    else if (hex->PlayerOwn() == 2)
                        {
                        hex->setScale(1.05);
                            hex->setBrush(QColor(223, 238, 25));
                     }
                    else
                        hex->setBrush(QColor(50, 146, 140));
                    lastHoveredHex = hex;
                }
            }

            return false;
        }

        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = view->mapToScene(mouseEvent->pos());

            if (view == ui->graphicsView) {
                HexagonItems* hex = getHexagonAtPosition(scenePos);
                if (hex)
                    qDebug() << "Clicked old hex at:" << hex->row << hex->col;
                else{
                    QMessageBox msgBox;
                     msgBox.setText("NO hex on that position.");
                     msgBox.exec();
                }

            } else if(view == ui->agentOne){
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos);
                if (agentHex){
                    qDebug() << "Clicked agent hex at position:" << agentHex->pos();
                        agentHex->HideAgents(agentHidden1, agentsOne);
                        agentHidden1 = !agentHidden1;
                }
            }
            else if(view == ui->agentTwo)
            {
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos);
                if (agentHex){
                    //qDebug() << "Clicked agent hex at position:" << agentHex->pos();
                    agentHex->HideAgents(agentHidden2, agentsTwo);
                    agentHidden2 = !agentHidden2;
                }
            }
            return false;
        }
    }
    return QWidget::eventFilter(obj, event);
}

HexagonItems* Widget::getHexagonAtPosition(const QPointF &pos)
{
    for (auto hex : hexMap) {
        if (hex->contains(hex->mapFromScene(pos))) {
            return hex;
        }

    }
    return nullptr;
}

void Widget::LoadingAgents(QGraphicsView *agent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    agent->setScene(scene);

    qreal hexSize = 30;

    qreal hDist = hexSize * std::sqrt(10);

    QVector<QPointF> positions ;
    if(agent == ui->agentOne)
    {
    positions = {
                {0, 0},
                {0, hDist *0.7},
                {0, hDist *1.4},

                {0, hDist*2.1},
                {0, hDist * 2.8},

                {0, 3.5 * hDist},
                {0, 4.5 * hDist},
                };
    }
    else if(agent == ui->agentTwo)
    {
        positions = {
                                      {100, 0},
                                      {100, hDist * 0.7},
                                      {100, hDist *1.4},

                                      {100, hDist*2.1},
                                      {100, hDist * 2.8},

                                      {100, 3.5 * hDist},
                                    {100, 4.5 * hDist},
                                      };
    }
    for (const QPointF& pos : positions) {
        hexagonAgents* hex;
        if(positions[0] == pos) hex = new hexagonAgents(hexSize, ":/near/Colonel_baba.webp");
        else if(positions[1] == pos) hex = new hexagonAgents(hexSize, ":/near/Gobi.webp");
        else if(positions[2] == pos) hex = new hexagonAgents(hexSize, ":/near/Kabu.webp");
        else if(positions[3] == pos) hex = new hexagonAgents(hexSize, ":/near/Kabu.webp");
        else if(positions[4] == pos) hex = new hexagonAgents(hexSize, ":/near/Salih.webp");
        else if(positions[5] == pos) hex = new hexagonAgents(hexSize, ":/near/Thor.webp");
        else
        {
        if(agent == ui->agentOne) hex = new hexagonAgents(hexSize+ 7, ":/near/youtubers_headline.webp");
        else if(agent == ui->agentTwo) hex = new hexagonAgents(hexSize+ 7, ":/near/valorant-header-1 (1).webp");
        }
        hex->setPos(pos);
        scene->addItem(hex);
        if(agent == ui->agentOne)
        {
            agentsOne.append(hex);
        }
        else if(agent == ui->agentTwo) agentsTwo.append(hex);
        this->agentHexList.append(hex);

    }
    QLabel* status;
    if(agent == ui->agentOne) status = new QLabel("👑 Ali Ahmad");
    else if(agent == ui->agentTwo) status = new QLabel("👑 Karim Benzima");
    status->setStyleSheet(
        "QLabel {"
        "  background-color: rgba(30, 30, 30, 180);"
        "  color: white;"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "  border: 2px solid #FFD700;"
        "  border-radius: 10px;"
        "  padding: 6px 12px;"
        "  font-family: 'Segoe UI', 'Arial';"
        "}"
        );
    QGraphicsProxyWidget* statusItem = scene->addWidget(status);
    statusItem->setZValue(100); // bring to front
    statusItem->setPos(-70, scene->height() + 70);
}

hexagonAgents* Widget::getAgentHexagonAtPosition(const QPointF &pos)
{
    for (auto agentHex : agentHexList) {
        if (agentHex->contains(agentHex->mapFromScene(pos))) {
            return agentHex;
        }
    }
    return nullptr;
=======
    ui->setupUi(this);

>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
}

Widget::~Widget()
{
    delete ui;
}
<<<<<<< HEAD
=======

void Widget::on_pushButton_clicked()
{
    hide();
    second *s = new second();
    s->show();

}

>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
