#ifndef FLYING_H
#define FLYING_H
#include "hexagonagents.h"
class Flying : public hexagonAgents
{
public:
    Flying(qreal size, const QString &imagePath, QGraphicsItem *parent = nullptr);
private:
    QString Name; // Billy, Abgus, ...
    int HP;
    int mobility;
    int Damage;
    int AttackRange;
    int PlayerOwn;
};

#endif
