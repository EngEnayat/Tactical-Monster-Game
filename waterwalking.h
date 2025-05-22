#ifndef WATERWALKING_H
#define WATERWALKING_H

#include "hexagonagents.h"
class WaterWalking : public hexagonAgents
{
public:
    WaterWalking(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
private:
    QString Name; // Billy, Abgus, ...
    int HP;
    int mobility;
    int Damage;
    int AttackRange;
    int PlayerOwn;
};

#endif // WATERWALKING_H
