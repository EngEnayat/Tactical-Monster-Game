#include "hexagonagents.h"
#include <QDebug>

hexagonAgents* hexagonAgents::SelectedAgents = nullptr;
int hexagonAgents::CurrentPlayer = 1;
QMap<QString, QString> hexagonAgents::nameToFilename =
     {
        {"Sir Lamorak", "Lamorak"},
        {"Eloi", "Eloi (1)"},
        {"Sir Philip", "Sir philiph"},
        {"Frust", "Frost"},
        {"Death", "death"},
        {"Rambu", "Rambo"},
        {"Colonel Baba", "Colonel_baba"}
};
QStringList hexagonAgents::FlyingList =
    {
        "Rambu"
};
QStringList hexagonAgents::GroundedList =
    {
        "Kabu",
        "Sir Lamorak",
        "Rajakal",
        "Salih",
        "Khan",
        "Boi",  // 6
        "Eloi",   // 7
        "Kanar",
        "Elsa",
        "Karissa",
        "Sir Philip",
        "Frust",
        "Tusk"  // 13
};

QStringList hexagonAgents::WaterAgentsList =
    {
        "Billy",
        "Reketon",
        "Duraham",
        "Angus",
        "Colonel Baba",
        "Medusa",
        "Bunka",
        "Sanka"
};
QStringList hexagonAgents::FloatingList =
    {
        "Sabrina",
        "Death"
};

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
    setPen(QPen(Qt::black, 1));
}

hexagonAgents* hexagonAgents::getSelectedAgent()
{
    return SelectedAgents;
}

void hexagonAgents::AgentClicked(QVector<hexagonAgents*> agentsList)
{
    qDebug() << this->GetName() << " Clicked";

    if (!this->isVisible()) return;

    bool isSelected = false;

    for (auto* agent : agentsList) {
        if (agent == this) {
            isSelected = true;
        }
    }

    if (!isSelected) return;

    // Deselect all agents
    for (auto* agent : agentsList) {
        if (agent == SelectedAgents) {
            agent->setScale(1.0);
        }
    }

    // Toggle selection
    if (SelectedAgents == this) {
        this->setScale(1.0);
        SelectedAgents = nullptr;
    } else {
        this->setScale(1.1);
        SelectedAgents = this;
    }

    for (auto* agent : agentsList) {
        agent->update();
    }
}

QString hexagonAgents::ImagePath(QString name)
{
    QString adjustedName = nameToFilename.contains(name) ? nameToFilename[name] : name;
    QString path = ":/preAgent/Agents/" + adjustedName + ".webp";
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
    for(int i=0; i<agents.size() ;++i)
    {
        agents[i]->setEnabled(false);
    }
}

void hexagonAgents::EnableAll(QVector<hexagonAgents *> agents)
{
    for(int i=0; i<agents.size() ;++i)
    {
        agents[i]->setEnabled(true);
    }
}

void hexagonAgents::SetType(QString name)
{
    Type = name;
}

QString hexagonAgents::getType()
{
    return Type;
}

void hexagonAgents::SetName(QString n)
{
    Name = n;
}

QString hexagonAgents::GetName()
{
    return Name;
}



