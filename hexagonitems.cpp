#include "hexagonitems.h"
#include <QColor>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
HexagonItems::HexagonItems(const QPolygonF& polygon, int row, int col)
    : QGraphicsPolygonItem(polygon), row(row), col(col) {}

void HexagonItems::setProperties(int player, bool occupied, QString type) {
    this->player = player;
    this->occupied = occupied;
    this->type = type;
    this->OriginalType = type;
}
void HexagonItems::getPro() const
{
    qDebug() << "Type: " << this->type;
    qDebug() << " Player: " << this->player;
    qDebug() << " occupied: " << (this->occupied ? "Yes" : "No") ;
}

int HexagonItems::PlayerOwn() const
{
    return player;
}

void HexagonItems::setPlacedAgent(hexagonAgents *p, QString where)
{

    if(where == "Attack")
    {
    this->placedAgent = p;
    if(p)p->setParentItem(this);
    return;
    }
    else{
    if(p)
    {
        placedAgent = nullptr;
        this->placedAgent = p;
    }
    if (p) {
        p->setParentItem(this);
    }
    }
}

hexagonAgents* HexagonItems::getPlacedAgent() const
{
    return placedAgent;
}

QString HexagonItems::agentName() const {
    return placedAgent ? placedAgent->GetName() : "None";
}

void HexagonItems::setPlayerOwn(int PlayerNew)
{
    player = PlayerNew;
}


void HexagonItems::highlight(QColor color)
{
    if (!highlighted) {
        highlighted = true;

        if (!this->hasAgent()) {
            originalColor = brush().color();
            setBrush(QBrush(color));
        }
        /*else {
            hexagonAgents* a = this->getPlacedAgent();
            originalPath = a->ImagePath(a->GetName());
        }*/
    }
}

void HexagonItems::unhighlight()
{
    if (!highlighted) return;

    highlighted = false;

    if (!this->hasAgent()) {
        this->resetColor();
    }

    /*else {
        this->setBrush(QBrush(QPixmap(originalPath).scaled(
            this->boundingRect().size().toSize(),
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            )));
        this->setScale(0.9);
    }*/
}

bool HexagonItems::hasAgent() const {
    return placedAgent != nullptr;
}
void HexagonItems::resetColor() {
    if (type == "One" && !this->occupied) setBrush(QColor(120, 170, 120)), this->setScale(1), this->setScale(0.9);
    else if (type == "Two" && !this->occupied) setBrush(QColor(255, 255, 100)), this->setScale(1), setScale(0.9);
    else if (type == "Water") setBrush(QColor(32, 107, 186)), this->setScale(0.9);
    else if (type == "Banned") setBrush(QColor(189, 40, 117)), setScale(0.9);
    else if(type == "Ground") setBrush(Qt::white);
    else if(player == 0) setBrush(Qt::white);
}
