#include "waterwalking.h"


WaterWalking::WaterWalking(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{

}

int WaterWalking::GetHp()
{
    return HP;
}

int WaterWalking::GetMobility()
{
    return mobility;
}

int WaterWalking::getDamage()
{
    return Damage;
}

int WaterWalking::GetAttackRange()
{
    return AttackRange;
}

int WaterWalking::GetPlayerOwn()
{
    return PlayerOwn;
}
