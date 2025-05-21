#include "widget.h"
#include "./ui_widget.h"
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
int Widget::PlayerTurn = 1;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    ui->agentOne->setMinimumWidth(150);
    ui->agentTwo->setMinimumWidth(150);

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
        hexItem->setProperties(10, false, ' ');
        hexItem->setBrush(Qt::white);
    }
    hexMap[{row, col}] = hexItem;

    hexItem->setPen(QPen(Qt::black, 1));
    hexItem->setScale(0.9);
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
                HoverHexagon(scenePos);
            }
            return false;
        }

        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = view->mapToScene(mouseEvent->pos());

            if (view == ui->graphicsView) {
                HexagonItems* hex = getHexagonAtPosition(scenePos);
                if (hex)
                    this->ClickHexagon(scenePos);
                else{
                    QMessageBox msgBox;
                     msgBox.setText("NO hex on that position.");
                     msgBox.exec();
                }

            } else if(view == ui->agentOne){
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos);
                if (agentHex){
                    qDebug() << "Clicked agent hex at position:" << agentHex->pos();
                        agentHex->HideAgents(agentsOne);
                }
            }
            else if(view == ui->agentTwo)
            {
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos);
                if (agentHex){
                    agentHex->HideAgents(agentsTwo);
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

void Widget::ClickHexagon(QPointF scenePos)
{

    if(!hexagonAgents::getSelectedAgent())
    {
        QMessageBox msgBox;
        msgBox.setText("NO Agent has selected!\nPlease first select one.");
        msgBox.exec();
        return;
    }


    HexagonItems *hexItem = getHexagonAtPosition(scenePos);
    hexagonAgents *hex = hexagonAgents::getSelectedAgent();

    if(hexItem->PlayerOwn() == 1 && PlayerTurn == 2)
    {
        QMessageBox msgBox;
        msgBox.setText("PLEASE set your agents on your own CELLS");
        msgBox.exec();
        return;
    }
    else if(hexItem->PlayerOwn() == 2 && PlayerTurn == 1)
    {
        QMessageBox msgBox;
        msgBox.setText("PLEASE set your agents on your own CELLS");
        msgBox.exec();
        return;
    }
    if(agentsOne.size()>=7 && PlayerTurn == 1)
    {
        agentsTwo[6]->setScale(1);
        agentsOne[6]->setEnabled(true);
        hex->InActive(agentsOne);
        hex->EnableAll(agentsTwo);
    }
    if(agentsTwo.size()>=7 && PlayerTurn == 2)
    {
        agentsOne[6]->setScale(1);
        agentsTwo[6]->setScale(1.1);
        agentsTwo[6]->setEnabled(true);
        hex->InActive(agentsTwo);
        hex->EnableAll(agentsOne);
    }

    QPixmap agentPixmap;
    if(hexItem->isOccupied())
    {
        QMessageBox msgBox;
        msgBox.setText("CELL is already occupied, try another.");
        msgBox.exec();
        return;
    }
    else if (hex && (hexItem->HexType() != '~' && hexItem->HexType() != '#' && hexItem->HexType() !=' ')){
        agentPixmap = QPixmap(hex->getAgentAddress(scenePos));
        hexItem->setBrush(Qt::NoBrush);
    }
    else return;

    hexItem->setBrush(QBrush(agentPixmap.scaled(
        hexItem->boundingRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        )));
    hex->setVisible(false);
    hex->setDropped(true);
    hex->setEnabled(false);
    hex->CleanSelection();
    hexItem->ChangeOccupied(true);
    hexItem->setScale(0.9);
    PlayerTurn = ((PlayerTurn == 1) ? 2 : 1);
}

void Widget::HoverHexagon(QPointF scenePos)
{
    if (lastHoveredHex && lastHoveredHex != getHexagonAtPosition(scenePos)) {
        lastHoveredHex->resetColor();
        lastHoveredHex = nullptr;
    }
    HexagonItems* hex = getHexagonAtPosition(scenePos);
    if (hex && hex != lastHoveredHex) {
        if (hex->PlayerOwn() == 1 && !hex->isOccupied() && PlayerTurn == 1)
        {
            hex->setScale(1.05);
            hex->setBrush(QColor(44, 118, 41));
        }
        else if (hex->PlayerOwn() == 2 && !hex->isOccupied() && PlayerTurn == 2)
        {
            hex->setScale(1.05);
            hex->setBrush(QColor(223, 238, 25));
        }
        lastHoveredHex = hex;
    }
}

void Widget::LoadingAgents(QGraphicsView *agent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    agent->setScene(scene);

    qreal hexSize = 25;

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

    QStringList agentImages = {
        ":/near/Colonel_baba.webp",
        ":/near/Gobi.webp",
        ":/near/Kabu.webp",
        ":/near/Kabu.webp",
        ":/near/Salih.webp",
        ":/near/Thor.webp"
    };
    for (const QPointF& pos : positions) {
        hexagonAgents* hex;
        if(positions[0] == pos){
            hex = new hexagonAgents(hexSize, agentImages[0]);
            hex->StoreAddress(pos, agentImages[0]);
        }
        else if(positions[1] == pos)
        {
            hex = new hexagonAgents(hexSize, agentImages[1]);
            hex->StoreAddress(pos, agentImages[1]);
        }
        else if(positions[2] == pos)
        {
            hex = new hexagonAgents(hexSize, agentImages[2]);
            hex->StoreAddress(pos, agentImages[2]);
        }
        else if(positions[3] == pos)
        {
            hex = new hexagonAgents(hexSize, agentImages[3]);
            hex->StoreAddress(pos, agentImages[3]);
        }
        else if(positions[4] == pos)
        {
            hex = new hexagonAgents(hexSize, agentImages[4]);
            hex->StoreAddress(pos, agentImages[4]);
        }
        else if(positions[5] == pos)
        {
            hex = new hexagonAgents(hexSize, agentImages[5]);
            hex->StoreAddress(pos, agentImages[5]);
        }

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
        hex->InActive(agentsTwo);
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
    statusItem->setZValue(100);
    statusItem->setPos(-70, scene->height() + 70);
}

hexagonAgents* Widget::getAgentHexagonAtPosition(const QPointF &pos)
{
    for (auto agentHex : agentHexList) {
        if (agentHex->contains(agentHex->mapFromScene(pos))) {
            if(!agentHex->isEnabled()) return nullptr;
            return agentHex;
        }
    }
    return nullptr;
}

Widget::~Widget()
{
    for(int i=0; i<agentHexList.size();i++)
    {
        delete agentHexList[i];
    }
    delete ui;
}
