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
    this->LoadingAgents(ui->agentOne, PlayerOneSelectedAgents);
    this->LoadingAgents(ui->agentTwo, PlayerTwoSelectedAgents);
    for(auto it: agentsOne)
        it->setEnabled(true);
    this->SetPropertiesAgents(agentsOne);
    this->SetPropertiesAgents(agentsTwo);
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
                HexagonItems* hex = getHexagonAtPosition(scenePos);
                if (hex)
                    this->ClickHexagon(scenePos);
                else{
                    QMessageBox msgBox;
                     msgBox.setText("NO hex on that position.");
                     msgBox.exec();
                }

            } else if(view == ui->agentOne){
                hexagonAgents* agentHex = getAgentHexagonAtPosition(scenePos, ui->agentOne);
                if (agentHex){
                    qDebug() << "Clicked agent hex at position:" << agentHex->pos();
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

void Widget::ClickHexagon(QPointF scenePos)
{
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
        for(auto it: agentsOne) it->setEnabled(false);
        for(auto it: agentsTwo) it->setEnabled(true);
    }
    if (PlayerTurn == 2) {
        for(auto it: agentsOne) it->setEnabled(true);
        for(auto it: agentsTwo) it->setEnabled(false);
    }

    if (hexItem->isOccupied()) {
        QMessageBox msgBox;
        msgBox.setText("CELL is already occupied, try another.");
        msgBox.exec();
        return;
    }

    if (hexItem->HexType() == '~' || hexItem->HexType() == '#' || hexItem->HexType() == ' ') {
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

    // Update hexagon appearance
    hexItem->setBrush(QBrush(agentPixmap.scaled(
        hexItem->boundingRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        )));

    hexItem->setScale(0.9);
    hexItem->ChangeOccupied(true);
    hexItem->setPlacedAgent(hex);
    qDebug() << hexItem->agentName() << " has dropped in hexItem";
    // Switch turn
    PlayerTurn = (PlayerTurn == 1) ? 2 : 1;
    // delete hex
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
            } else if (type == "Flying") {
                hex = new Flying(hexSize, imagePath);
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
                qDebug() << "Created" << type << "agent:" << agentName;
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
        pos += QPointF(30, -30);
    } else {
        pos += QPointF(-30, 70);
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
