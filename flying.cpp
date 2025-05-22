#include "flying.h"

Flying::Flying(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{
}

int Flying::GetHp()
{
    return HP;
}

int Flying::GetMobility()
{
    return mobility;
}

int Flying::getDamage()
{
    return Damage;
}

int Flying::GetAttackRange()
{
    return AttackRange;
}

int Flying::GetPlayerOwn()
{
    return PlayerOwn;
}
