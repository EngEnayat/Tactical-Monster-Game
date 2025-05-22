#ifndef FLOATING_H
#define FLOATING_H
#include "hexagonagents.h"
class Floating : public hexagonAgents
{
public:
    Floating(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
    int GetHp();
    int GetMobility();
    int getDamage();
    int GetAttackRange();
    int GetPlayerOwn();

private:
    QString Name = "FlY"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
};

#endif
