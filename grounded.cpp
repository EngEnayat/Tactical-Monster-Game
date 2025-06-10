#include "grounded.h"

Grounded::Grounded(qreal size, const QString& imagePath, QGraphicsItem* parent)
    : hexagonAgents(size, imagePath, parent)
{
    // Initialize default stats or load from file later
    if(this->GetName()  =="Sir Philip" )
    {
        this->HP = 400;
        this->mobility = 2;
        this->Damage = 100;
        this->AttackRange = 1;
    }
    else if(this->GetName()  =="Sir Lamorak" )
    {
        this->HP = 320;
        this->mobility = 3;
        this->Damage = 110;
        this->AttackRange = 1;
    }
}

int Grounded::GetHp() const { return HP; }
int Grounded::GetMobility() const { return mobility; }
int Grounded::getDamage() const { return Damage; }
int Grounded::GetAttackRange() const { return AttackRange; }
int Grounded::GetPlayerOwn() const { return PlayerOwn; }

void Grounded::setHP(int hp) { HP = hp; }
void Grounded::setMobility(int m) { mobility = m; }
void Grounded::setDamage(int d) { Damage = d; }
void Grounded::setAttackRange(int r) { AttackRange = r; }
void Grounded::setPlayerOwn(int p) { PlayerOwn = p; }

QString Grounded::getAgentType() const { return AgentType; }


bool Grounded::WaterMoving(){return false;}
bool Grounded::GroundMoving(){return true;}
bool Grounded::BannedMoving(){return false;}

bool Grounded::CanStayGround(){return true;}
bool Grounded::CanStayWater(){return false;}
bool Grounded::canStayBanned() {return false;}
