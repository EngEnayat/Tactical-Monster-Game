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
#include <queue>
#include "grounded.h"
#include "waterwalking.h"
#include "floating.h"
#include "flying.h"

//                                          HOW to deal with many datatypes
// Grounded *m = new Grounded(23, "f", nullptr);
// hexagonAgents *n = m;
// if (auto* groundedAgent = dynamic_cast<Grounded*>(n)) {
//     groundedAgent->specialGroundedMethod();  // ✅ Safe and works
// };


int Widget::PlayerTurn = 1;
int Widget::DroppedCount = 0;

Widget::Widget(QStringList PlayerOneSelectedAgents ,QStringList PlayerTwoSelectedAgents ,QWidget *parent)
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

    qDebug() << "Created";
    QFile file(":/grids/grid1.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines << in.readLine();
        }
        file.close();

        for (int row = 0, gridRow = 0; row < lines.size()-1; row++) {
            const QString &line = lines[row];
            for (int col = 0, gridCol = 0; col < line.length()-1; ) {
                if (line[col] == '/') {
                    QChar ch = line[col+1];
                    if (ch == '\\' || ch == '_' || ch == '|') {
                        col += 2;
                        continue;
                    }

                    qreal x = (col / 6.0) * hexWidth * 1.5;
                    qreal y = row * hexHeight * 0.5;
                    createHexagon(x, y, ch, row, col / 6);
                    HexagonItems * h = getHexagonAtPosition(QPointF(x,y));
                    // if(gridCol<9)
                    col += 5;
                }
                else {
                    col++;
                }
            }
        }
    }


    this->LoadingAgents(ui->agentOne, PlayerOneSelectedAgents);
    this->LoadingAgents(ui->agentTwo, PlayerTwoSelectedAgents);
    for(auto it: agentsOne)
        it->setEnabled(true);
    this->SetPropertiesAgents(agentsOne);
    this->SetPropertiesAgents(agentsTwo);
    this->AddHexNeighbor();
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

    hexMap[{row, col}] = hexItem;

    hexItem->setPos(x, y);

    if (ch == '1') {
        hexItem->setProperties(1, false, "One");
        hexItem->setBrush(QColor(120,170,120));
    } else if (ch == '2') {
        hexItem->setProperties(2, false, "Two");
        hexItem->setBrush(QColor(255, 255, 100));
    } else if (ch == '#') {
        hexItem->setProperties(0, true, "Water");
        hexItem->setBrush(QColor(32, 107, 186));
    } else if (ch == '~') {
        hexItem->setProperties(0, true, "Banned");
        hexItem->setBrush(QColor(189, 40, 117));
    } else {
        hexItem->setProperties(10, false, "Ground");
        hexItem->setBrush(Qt::white);
    }

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
                if(DroppedCount <=11)HoverHexagon(scenePos);
            }
            else if(view == ui->agentOne)
                HoverAgents(scenePos, 1);
            else if(view == ui->agentTwo)
                HoverAgents(scenePos, 2);
            return false;
        }

        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF scenePos = view->mapToScene(mouseEvent->pos());

            if (view == ui->graphicsView) {

                if(!hexagonAgents::getSelectedAgent() && DroppedCount <=11)
                    qDebug() << "Invalid hex";

                else if(DroppedCount > 11){
                HexagonItems* hex = getHexagonAtPosition(scenePos);
                if (hex)
                    this->ClickHexagon(scenePos);
                    // qDebug() << "Clicked on agent" ;
                }
                else{
                HexagonItems* hex = getHexagonAtPosition(scenePos);
                if (hex)
                    this->ClickHexagon(scenePos);
                else{
                    QMessageBox msgBox;
                     msgBox.setText("NO hex on that position.");
                     msgBox.exec();
                }
                }

            } else if(view == ui->agentOne){
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos, ui->agentOne);
                if (agentHex){
                        agentHex->AgentClicked(agentsOne);
                }
            }
            else if(view == ui->agentTwo)
            {
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos, ui->agentTwo);
                if (agentHex){
                    agentHex->AgentClicked(agentsTwo);
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

bool Widget::CheckAttack(HexagonItems* TargetHex)
{
    qDebug() << "Top of Check Attack";
    if(!lastClickedHex) return false;
    else if (!lastVisited.contains(TargetHex)) return false;
    if(lastClickedHex->getPlacedAgent()->getType() != TargetHex->HexType()) return false;

    if (TargetHex->getPlacedAgent() != nullptr || TargetHex->HexType() == "Banned")
        return false;

    qDebug() << "INSIDE the check ATtack";
    TargetHex->setPlacedAgent(lastClickedHex->getPlacedAgent());

    QString path = lastClickedHex->getPlacedAgent()->ImagePath(lastClickedHex->getPlacedAgent()->GetName());
    TargetHex->setBrush(QBrush(QPixmap(path).scaled(
        TargetHex->boundingRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        )));
    TargetHex->setScale(0.9);
    TargetHex->setPlayerOwn(lastClickedHex->PlayerOwn());

    if(lastClickedHex->getOriginalType() == "One")
        lastClickedHex->setBrush(QColor(120,170,120));
    else if(lastClickedHex->getOriginalType() == "Two")
        lastClickedHex->setBrush(QColor(255, 255, 100));
    else if(lastClickedHex->getOriginalType() == "Water")
        lastClickedHex->setBrush(QColor(32, 107, 186));
    else if(lastClickedHex->getOriginalType() =="Ground")
        lastClickedHex->setBrush(Qt::white);

    lastClickedHex = nullptr;

    PlayerTurn = (PlayerTurn == 1)? 2 : 1;

    for (HexagonItems* hex : lastVisited) {
        hex->unhighlight();
    }
    lastVisited.clear();
    qDebug() << "last of Check Attack";

    return true;
}

void Widget::ClickHexagon(QPointF scenePos)
{
    if(DroppedCount>11){
        HexagonItems* start = getHexagonAtPosition(scenePos);

        if(!start) return;

        if(PlayerTurn != start->getPlacedAgent()->GetPlayerOwn() || lastClickedHex) return;
        qDebug() << "Calling AttaCk";

        if(!CheckAttack(start)) return;

        qDebug() << "AFTER check Attack";
        if(start->getPlacedAgent())
        {
            hexagonAgents *placed = start->getPlacedAgent();
            this->BFS(start, placed->GetMobility());
        }
        
        else qDebug() << "No Agent has Placed at that cell";
        return;
    }

    if (!hexagonAgents::getSelectedAgent()) {
        QMessageBox msgBox;
        msgBox.setText("NO Agent has selected!\nPlease first select one.");
        msgBox.exec();
        return;
    }

    HexagonItems *hexItem = getHexagonAtPosition(scenePos);
    hexagonAgents *hex = hexagonAgents::getSelectedAgent();

    if ((hexItem->PlayerOwn() == 1 && PlayerTurn == 2) ||
        (hexItem->PlayerOwn() == 2 && PlayerTurn == 1)) {
        QMessageBox msgBox;
        msgBox.setText("PLEASE set your agents on your own CELLS");
        msgBox.exec();
        return;
    }

    if (PlayerTurn == 1) {
        for(auto it: std::as_const(agentsOne)) it->setEnabled(false);
        for(auto it: std::as_const(agentsTwo)) it->setEnabled(true);
    }
    if (PlayerTurn == 2) {
        for(auto it: std::as_const(agentsOne)) it->setEnabled(true);
        for(auto it: std::as_const(agentsTwo)) it->setEnabled(false);
    }

    if (hexItem->isOccupied()) {
        QMessageBox msgBox;
        msgBox.setText("CELL is already occupied, try another.");
        msgBox.exec();
        return;
    }

    if (hexItem->HexType() == "Ground" || hexItem->HexType() == "Water" || hexItem->HexType() == "Banned") {
        return;
    }

    QString add;
    add = hex->ImagePath(hex->GetName());
    //Get image path and load pixmap
    QPixmap agentPixmap(add);
    if (agentPixmap.isNull()) {
        qDebug() << "Failed to load image.";
        return;
    }

    QString type = hex->getType();

    hex->setVisible(false);
    hex->setEnabled(false);

    hex->setScale(0.9);
    hex->setDropped(true);
    hex->CleanSelection();


    scene->addItem(hex);
    activeAgents.append(hex);

    hexItem->setBrush(QBrush(agentPixmap.scaled(
        hexItem->boundingRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        )));

    hexItem->setScale(0.9);
    hexItem->ChangeOccupied(true);
    hexItem->setPlacedAgent(hex);
    qDebug() << hexItem->agentName() << " has dropped in hexItem";
    PlayerTurn = (PlayerTurn == 1) ? 2 : 1;
    DroppedCount++;
}

void Widget::BFS(HexagonItems* start, int MapDepth)
{
    
    if(lastClickedHex) return;

    if (!start || MapDepth <= 0) return;
    qDebug() << "TOP of BFS";
    QVector<HexagonItems*> visited;
    std::queue<QPair<HexagonItems*, int>> Queue;

    visited.append(start);
    Queue.push(qMakePair(start, 0));

    while (!Queue.empty()) {
        QPair<HexagonItems*, int> current = Queue.front();
        Queue.pop();

        HexagonItems* hex = current.first;
        int depth = current.second;

        if (depth >= MapDepth)
            continue;

        for (HexagonItems* neighbor : hex->getNeighbors()) {
            if (!visited.contains(neighbor)) {
                visited.append(neighbor);
                Queue.push(qMakePair(neighbor, depth + 1));
            }
        }
    }

    //!hex->getPlacedAgent() &&
    //if(lastClickedHex) qDebug() << "The Clicked Agent type: " << lastClickedHex->HexType() << "\nAnd its neighbors types";


    lastVisited = visited;
    lastClickedHex = start;

    for (HexagonItems* hex : std::as_const(visited)) {
       // qDebug() << hex->HexType();
        if ( hex->HexType() != "Banned") {
           if(!lastClickedHex)
                continue;
            if( lastClickedHex->hasAgent())
            {
                hex->highlight(Qt::red);
            }
        }
    }
    qDebug() << "LAST of BFS" << "\n THE last hex: " << lastClickedHex->getPlacedAgent()->GetName();

}

void Widget::AddHexNeighbor()
{
    qreal expectedDistance = hexWidth * 0.87;
    qreal tolerance = hexWidth * 0.15;

    for (HexagonItems* h1 : hexMap) {
        QPointF pos1 = h1->scenePos();

        for (HexagonItems* h2 : hexMap) {
            if (h1 == h2) continue;

            QPointF pos2 = h2->scenePos();
            qreal dist = QLineF(pos1, pos2).length();

            if (qAbs(dist - expectedDistance) < tolerance) {
                h1->addNeighbor(h2);
            }
        }
    }
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

void Widget::LoadingAgents(QGraphicsView *agent, QStringList PlayerAgents)
{
    int CurrentTurn = (agent == ui->agentOne) ? 1 : 2;
    QGraphicsScene* scene = new QGraphicsScene(this);
    agent->setScene(scene);

    qreal hexSize = 25;
    qreal hDist = hexSize * std::sqrt(10);
    QVector<QPointF> positions = (agent == ui->agentOne)
                                     ? QVector<QPointF>({ {0, 0}, {0, hDist * 0.7}, {0, hDist * 1.4}, {0, hDist * 2.1}, {0, hDist * 2.8}, {0, 3.5 * hDist} })
                                     : QVector<QPointF>({ {100, 0}, {100, hDist * 0.7}, {100, hDist * 1.4}, {100, hDist * 2.1}, {100, hDist * 2.8}, {100, 3.5 * hDist} });

    qDebug() << "Player " << CurrentTurn << " Agent Types";

    for (int i = 0; i < positions.size(); ++i) {
        hexagonAgents* hex = nullptr;
        QString agentName = (i < PlayerAgents.size()) ? PlayerAgents[i] : "";

        if (!agentName.isEmpty())
        {
            QString type;
            if (hexagonAgents::GroundedList.contains(agentName)) {
                type = "Grounded";
            } else if (hexagonAgents::WaterAgentsList.contains(agentName)) {
                type = "Water Walking";
            } else if (hexagonAgents::FloatingList.contains(agentName)) {
                type = "Floating";
            } else if (hexagonAgents::FlyingList.contains(agentName)) {
                type = "Flying";
            } else {
                qDebug() << "Unknown agent name:" << agentName;
                continue;
            }

            QString imagePath = hexagonAgents::ImagePath(agentName);
            if (type == "Grounded") {
                hex = new Grounded(hexSize, imagePath);
                hex->SetType("Ground");
                if(agentName == "Sir Lamorak")
                {
                    hex->SetName("Sir Lamorak");
                    hex->setHP(320);
                    hex->setMobility(3);
                    hex->setDamage(110);
                    hex->setAttackRange(1);
                }
                else if(agentName == "Sir Philip")
                {
                    hex->SetName("Sir Philip");
                    hex->setHP(400);
                    hex->setMobility(2);
                    hex->setDamage(100);
                    hex->setAttackRange(1);
                }
            } else if (type == "Water Walking") {
                hex = new WaterWalking(hexSize, imagePath);
                hex->SetType("Water");
                if(agentName == "Colonel Baba")
                {
                    hex->SetName("Colonel Baba");
                    hex->setHP(400);
                    hex->setMobility(2);
                    hex->setDamage(100);
                    hex->setAttackRange(1);
                }
            } else if (type == "Floating") {
                hex = new Floating(hexSize, imagePath);
                hex->SetType("Float");
            } else if (type == "Flying") {
                hex = new Flying(hexSize, imagePath);
                    hex->SetType("Fly");
            }

            if (hex) {
                hex->setPos(positions[i]);
                scene->addItem(hex);
                if (agent == ui->agentOne){
                    hex->setPlayerOwn(1);
                    agentsOne.append(hex);}
                else if (agent == ui->agentTwo){
                    agentsTwo.append(hex);
                    hex->setPlayerOwn(2);
                }
                agentHexList.append(hex);
                hex->SetName(agentName);
                hex->SetType(type);
            }
        }

        if (hex && (agent == ui->agentOne || agent == ui->agentTwo)) {
            QVector<hexagonAgents*>& agentList = (agent == ui->agentOne) ? agentsOne : agentsTwo;
            hex->InActive(agentList);
        }
    }

    QLabel* status = new QLabel((agent == ui->agentOne) ? "👑 Ali Ahmad" : "👑 Karim Benzima");
    status->setStyleSheet("QLabel { background-color: rgba(30, 30, 30, 180); color: white; font-size: 20px; font-weight: bold; border: 2px solid #FFD700; border-radius: 10px; padding: 6px 12px; font-family: 'Segoe UI', 'Arial'; }");
    QGraphicsProxyWidget* statusItem = scene->addWidget(status);
    statusItem->setZValue(100);
    statusItem->setPos(-70, scene->height() + 70);
}

hexagonAgents* Widget::getAgentHexagonAtPosition(const QPointF &pos, QGraphicsView* currentView)
{
    for (auto agentHex : agentHexList) {
        if (!agentHex || !agentHex->scene()) continue;

        QPointF itemPos = agentHex->mapFromScene(pos);

        if (currentView == ui->agentOne && !agentsOne.contains(agentHex)) continue;
        if (currentView == ui->agentTwo && !agentsTwo.contains(agentHex)) continue;

        if (!agentHex->boundingRect().contains(itemPos)) continue;

        if (agentHex->contains(itemPos)) {
            if (!agentHex->isEnabled()) return nullptr;
            return (agentHex->isVisible()) ? agentHex: nullptr;
        }
    }
    return nullptr;
}

void Widget::HoverAgents(QPointF p, int player)
{
    hexagonAgents *h = (player == 1)
                           ? getAgentHexagonAtPosition(p, ui->agentOne)
                           : getAgentHexagonAtPosition(p, ui->agentTwo);

    if (!h) {
        if (hoverInfoProxy[player - 1]) {
            hoverInfoProxy[player - 1]->hide();
        }
        return;
    }
    QGraphicsScene* sceneToShow = (player == 1)
                                      ? ui->agentOne->scene()
                                      : ui->agentTwo->scene();

    if (!sceneToShow) {
        qDebug() << "No scene found for player" << player;
        return;
    }

    if (!hoverLabel[player - 1]) {
        QLabel* label = new QLabel();
        label->setStyleSheet(
            "background-color: rgba(40, 40, 40, 220);"
            "color: white;"
            "padding: 8px 12px;"
            "border-radius: 6px;"
            "font-family: 'Segoe UI';"
            "font-size: 12px;");
        label->setFixedWidth(150);
        label->setWordWrap(true);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        hoverLabel[player - 1] = label;

        QGraphicsProxyWidget* proxy = sceneToShow->addWidget(label);
        proxy->setZValue(1000);
        hoverInfoProxy[player - 1] = proxy;
    }

    // Set text
    QString text = QString("<b>%1</b><br/>HP: %2<br/>Mobility: %3<br/>Damage: %4<br/>Attack Range: %5")
                       .arg(h->GetName())
                       .arg(h->GetHp())
                       .arg(h->GetMobility())
                       .arg(h->getDamage())
                       .arg(h->GetAttackRange());

    hoverLabel[player - 1]->setText(text);
    hoverLabel[player - 1]->adjustSize();

    QPointF pos = h->pos();
    if (player == 1) {
        pos += QPointF(10, -30);
    } else {
        pos += QPointF(-170, 0);
    }

    if (hoverInfoProxy[player - 1]->scene() != sceneToShow) {
        qWarning() << "Tooltip was added to wrong scene!";
        return;
    }

    hoverInfoProxy[player - 1]->setPos(pos);
    hoverInfoProxy[player - 1]->show();
}

void Widget::SetPropertiesAgents(QVector<hexagonAgents *> agents)
{
    if (agents.isEmpty()) return;

    QMap<QString, QString> typeToFile = {
        {"Grounded", ":/grids/Ground.txt"},
        {"Water Walking", ":/grids/Water.txt"},
        {"Floating", ":/grids/Floating.txt"},
        {"Flying", ":/grids/Flying.txt"}
    };
    for (hexagonAgents* agent : agents)
    {
        QString type = agent->getType();
        QString agentName = agent->GetName();

        if (type.isEmpty() || agentName.isEmpty()) continue;

        QString filePath = typeToFile.value(type);
        if (filePath.isEmpty()) {
            qDebug() << "No property file found for type:" << type;
            continue;
        }

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open property file:" << filePath;
            continue;
        }

        QTextStream in(&file);
        bool found = false;

        while (!in.atEnd() && !found) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.size() < 5) continue;

            QString nameInFile = parts[0];

            if (nameInFile == agentName) {
                bool ok;
                int hp = parts[1].toInt(&ok);
                int mobility = parts[2].toInt(&ok);
                int damage = parts[3].toInt(&ok);
                int attackRange = parts[4].toInt(&ok);

                if (!ok) {
                    qDebug() << "Invalid numeric value in file for agent:" << agentName;
                    continue;
                }
                    agent->setHP(hp);
                    agent->setMobility(mobility);
                    agent->setDamage(damage);
                    agent->setAttackRange(attackRange);
                qDebug() << "Set properties for" << type << "agent:" << agentName
                         << "| HP:" << hp
                         << "| Mobility:" << mobility
                         << "| Damage:" << damage
                         << "| Attack Range:" << attackRange;

                found = true;
            }
        }

        if (!found) {
            qDebug() << "No matching entry found for agent:" << agentName << "of type:" << type;
        }

        file.close();
    }
    qDebug() << "For Player ";
    for(auto it: agents)
    {
        qDebug() << "Name " << it->GetName();
        qDebug() << "PlayerOwn " << it->GetPlayerOwn();
        qDebug() << "HP: " << it->GetHp();
        qDebug() << "Mobility: " << it->GetMobility();
        qDebug() << "Type: " << it->getType();
        qDebug() << "Attack Range: " << it->GetAttackRange();
    }
}

Widget::~Widget()
{
    for(int i=0; i<agentHexList.size();i++)
    {
        delete agentHexList[i];
    }
    for(auto it: activeAgents)
        delete it;
    delete ui;
}
