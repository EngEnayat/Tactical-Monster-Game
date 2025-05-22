#include "grounded.h"

Grounded::Grounded(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{

}

int Grounded::GetHp()
{
    return HP;
}

int Grounded::GetMobility()
{
    return mobility;
}

int Grounded::getDamage()
{
    return Damage;
}

int Grounded::GetAttackRange()
{
    return AttackRange;
}

int Grounded::GetPlayerOwn()
{
    return PlayerOwn;
}
