#include "waterwalking.h"


WaterWalking::WaterWalking(qreal size, const QString &imagePath, QGraphicsItem *parent):
    hexagonAgents(size, imagePath, parent)
{
    if(this->GetName() == "Colonel Baba")
    {
        this->HP = 400;
        this->mobility = 2;
        this->Damage = 100;
        this->AttackRange = 1;
    }
}

int WaterWalking::GetHp() const { return HP; }
int WaterWalking::GetMobility() const { return mobility; }
int WaterWalking::getDamage() const { return Damage; }
int WaterWalking::GetAttackRange() const { return AttackRange; }
int WaterWalking::GetPlayerOwn() const { return PlayerOwn; }

void WaterWalking::setHP(int hp) { HP = hp; }
void WaterWalking::setMobility(int m) { mobility = m; }
void WaterWalking::setDamage(int d) { Damage = d; }
void WaterWalking::setAttackRange(int r) { AttackRange = r; }
void WaterWalking::setPlayerOwn(int p) { PlayerOwn = p; }

QString WaterWalking::getAgentType() const
{
    return AgentType;
}


bool WaterWalking::WaterMoving(){return true;}
bool WaterWalking::GroundMoving(){return true;}
bool WaterWalking::BannedMoving(){return false;}

bool WaterWalking::CanStayGround(){return true;}
bool WaterWalking::CanStayWater(){return true;}
bool WaterWalking::canStayBanned() {return false;}
