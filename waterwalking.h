#ifndef WATERWALKING_H
#define WATERWALKING_H

#include "hexagonagents.h"
class WaterWalking : public hexagonAgents
{
public:
    WaterWalking(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
    int GetHp();
    int GetMobility();
    int getDamage();
    int GetAttackRange();
    int GetPlayerOwn();

private:
    QString Name = "Water"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
};

#endif // WATERWALKING_H
