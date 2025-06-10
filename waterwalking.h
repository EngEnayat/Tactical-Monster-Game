#ifndef WATERWALKING_H
#define WATERWALKING_H

#include "hexagonagents.h"
class WaterWalking : public hexagonAgents
{
public:
    WaterWalking(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
    int GetHp() const override;
    int GetMobility() const override;
    int getDamage() const override;
    int GetAttackRange() const override;
    int GetPlayerOwn() const override;

    void setHP(int hp) override;
    void setMobility(int m) override;
    void setDamage(int d) override;
    void setAttackRange(int r) override;
    void setPlayerOwn(int p) override;
    QString getAgentType() const override;


    bool WaterMoving() override;
    bool GroundMoving() override;
    bool BannedMoving() override;
    bool CanStayGround() override;
    bool CanStayWater() override;
    bool canStayBanned() override;
private:
    QString Name = "Water"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
    QString AgentType = "Water";
};

#endif // WATERWALKING_H
