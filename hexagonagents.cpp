#include "hexagonagents.h"
#include <QDebug>

hexagonAgents* hexagonAgents::SelectedAgents = nullptr;


hexagonAgents::hexagonAgents(qreal size, const QString& imagePath, QGraphicsItem* parent)
    : QGraphicsPolygonItem(parent), pix(imagePath)
{
    QPolygonF hexagon;
    for (int i = 0; i < 6; ++i) {
        qreal angle_deg = 60 * i - 30;
        qreal angle_rad = M_PI / 180 * angle_deg;
        qreal x = size * cos(angle_rad);
        qreal y = size * sin(angle_rad);
        hexagon << QPointF(x, y);
    }
    setPolygon(hexagon);
    if (imagePath == "f")
        this->setBrush(QColor(44,139,33));
    setPen(QPen(Qt::black, 1));
    this->setVisible(false);
}

hexagonAgents* hexagonAgents::getSelectedAgent()
{
    return SelectedAgents;
}

void hexagonAgents::HideAgents(bool isHide, QVector<hexagonAgents*> agents)
{
    bool isAgent = false;

    if (agents.contains(this)) {
        if (this == agents[6]) {
            for (auto it : agents) {
                it->setVisible(!isHide);
            }
        } else {
            isAgent = true;
        }
    }
    agents[6]->setVisible(true);

    if (isAgent) {
        if (SelectedAgents && SelectedAgents != this) {
            SelectedAgents->setScale(1.0);
        }
        if (SelectedAgents == this) {
            this->setScale(1.0);
            SelectedAgents = nullptr;
        } else {
            this->setScale(1.1);
            SelectedAgents = this;
        }
    }
}

void hexagonAgents::StoreAddress(QPointF pos, QString path)
{
    HexAddress.insert(qMakePair(pos.x(), pos.y()), path);
}

QString hexagonAgents::getAgentAddress(QPointF pos)
{

}
