#ifndef FLYING_H
#define FLYING_H
#include "hexagonagents.h"
class Flying : public hexagonAgents
{
public:
    Flying(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
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
    QString Name = "Float"; // Billy, Abgus, ...
    int HP = 1;
    int mobility = 10;
    int Damage = 10;
    int AttackRange = 10;
    int PlayerOwn = 10;
};

#endif
