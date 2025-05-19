#include "hexagonitems.h"
#include <QColor>
#include <QBrush>
HexagonItems::HexagonItems(const QPolygonF& polygon, int row, int col)
    : QGraphicsPolygonItem(polygon), row(row), col(col) {}

void HexagonItems::setProperties(int player, bool occupied, char type) {
    this->player = player;
    this->occupied = occupied;
    this->type = type;
}
void HexagonItems::getPro()
{
    qDebug() << "Type: " << this->type;
    qDebug() << " Player: " << this->player;
    qDebug() << " occupied: " << (this->occupied ? "Yes" : "No") ;
}
int HexagonItems::PlayerOwn() const
{
    return player;
}
void HexagonItems::resetColor() {
    if (type == '1') setBrush(QColor(120, 170, 120)), this->setScale(1);
    else if (type == '2') setBrush(QColor(255, 255, 100)), this->setScale(1);
    else if (type == '#') setBrush(QColor(32, 107, 186));
    else if (type == '~') setBrush(QColor(189, 40, 117));
    else setBrush(Qt::white);
}
