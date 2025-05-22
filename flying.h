#ifndef FLYING_H
#define FLYING_H
#include "hexagonagents.h"
class Flying : public hexagonAgents
{
public:
    Flying(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
    int GetHp();
    int GetMobility();
    int getDamage();
    int GetAttackRange();
    int GetPlayerOwn();

private:
    QString Name = "Float"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
};

#endif
