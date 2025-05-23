#ifndef GROUNDED_H
#define GROUNDED_H
#include "hexagonagents.h"
class Grounded : public hexagonAgents
{
public:
    Grounded(qreal, const QString&, QGraphicsItem* parent = nullptr);

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
private:
    QString Name = "Ground"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
};
#endif
