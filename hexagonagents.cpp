#include "hexagonagents.h"
#include <QDebug>

hexagonAgents* hexagonAgents::SelectedAgents = nullptr;
int hexagonAgents::CurrentPlayer = 1;

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

void hexagonAgents::HideAgents(QVector<hexagonAgents*> agentsList)
{
    if (agentsList.size() < 7) return;
    if(!agentsList[6]->isEnabled()) return;
    if (this == agentsList[6]) {
        bool allDropped = true;

        for (int i = 0; i < 6; ++i) {
            if (!agentsList[i]->IsDropped) {
                allDropped = false;
                break;
            }
        }

        if (allDropped) {
            this->setVisible(false);
            return;
        }

        bool anyVisible = false;
        for (int i = 0; i < 6; ++i) {
            if (!agentsList[i]->IsDropped && agentsList[i]->isVisible()) {
                anyVisible = true;
                break;
            }
        }

        bool newState = !anyVisible;

        for (int i = 0; i < 6; ++i) {
            if (!agentsList[i]->IsDropped) {
                agentsList[i]->setVisible(newState);
            }
        }
        this->setVisible(true);
        return;
    }

    // Handle normal agent selection
    for (int i = 0; i < 6; ++i) {
        if (this == agentsList[i]) {
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
            break;
        }
    }
}
void hexagonAgents::StoreAddress(QPointF pos, QString path)
{
    HexAddress.insert(qMakePair(pos.x(), pos.y()), path);
}

QString hexagonAgents::getAgentAddress(QPointF pos)
{
    QString path =  HexAddress[qMakePair(this->x(), this->y())];
    return path;
}

void hexagonAgents::CleanSelection()
{
    SelectedAgents = nullptr;
}

void hexagonAgents::ChangePlayer()
{
    CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;
}

int hexagonAgents::PlayerTurn()
{
    return CurrentPlayer;
}

void hexagonAgents::InActive(QVector<hexagonAgents *> agents)
{
    for(int i=0; i<agents.size() -1 ;++i)
    {
        agents[i]->setEnabled(false);
    }
}

void hexagonAgents::EnableAll(QVector<hexagonAgents *> agents)
{
    for(int i=0; i<agents.size() -1 ;++i)
    {
        agents[i]->setEnabled(true);
    }
}

