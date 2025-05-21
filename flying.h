#ifndef FLYING_H
#define FLYING_H
#include "hexagonagents.h"
class Flying : public hexagonAgents
{
public:
    Flying();
private:
    QString Name; // Billy, Abgus, ...
    int HP;
    int mobility;
    int Damage;
    int AttackRange;
    int PlayerOwn;
};

#endif
