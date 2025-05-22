#ifndef GROUNDED_H
#define GROUNDED_H
#include "hexagonagents.h"
class Grounded : public hexagonAgents
{
public:
    Grounded(qreal, const QString&, QGraphicsItem* parent = nullptr);
    int GetHp();
    int GetMobility();
    int getDamage();
    int GetAttackRange();
    int GetPlayerOwn();

private:
    QString Name = "Ground"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
};
#endif
