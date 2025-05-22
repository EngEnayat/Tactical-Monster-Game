#include "floating.h"

Floating::Floating(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{

}

int Floating::GetHp()
{
    return HP;
}

int Floating::GetMobility()
{
    return mobility;
}

int Floating::getDamage()
{
    return Damage;
}

int Floating::GetAttackRange()
{
    return AttackRange;
}

int Floating::GetPlayerOwn()
{
    return PlayerOwn;
}
