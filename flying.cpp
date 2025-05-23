#include "flying.h"

Flying::Flying(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{
}

int Flying::GetHp() const { return HP; }
int Flying::GetMobility() const { return mobility; }
int Flying::getDamage() const { return Damage; }
int Flying::GetAttackRange() const { return AttackRange; }
int Flying::GetPlayerOwn() const { return PlayerOwn; }

void Flying::setHP(int hp) { HP = hp; }
void Flying::setMobility(int m) { mobility = m; }
void Flying::setDamage(int d) { Damage = d; }
void Flying::setAttackRange(int r) { AttackRange = r; }
void Flying::setPlayerOwn(int p) { PlayerOwn = p; }
