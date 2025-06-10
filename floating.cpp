#include "floating.h"

Floating::Floating(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{

}

int Floating::GetHp() const { return HP; }
int Floating::GetMobility() const { return mobility; }
int Floating::getDamage() const { return Damage; }
int Floating::GetAttackRange() const { return AttackRange; }
int Floating::GetPlayerOwn() const { return PlayerOwn; }

void Floating::setHP(int hp) { HP = hp; }
void Floating::setMobility(int m) { mobility = m; }
void Floating::setDamage(int d) { Damage = d; }
void Floating::setAttackRange(int r) { AttackRange = r; }
void Floating::setPlayerOwn(int p) { PlayerOwn = p; }

QString Floating::getAgentType() const
{
    return AgentType;
}

bool Floating::WaterMoving(){return true;}
bool Floating::GroundMoving(){return true;}
bool Floating::BannedMoving(){return true;}
bool Floating::CanStayGround(){return true;}
bool Floating::CanStayWater(){return true;}
bool Floating::canStayBanned() {return true;}
