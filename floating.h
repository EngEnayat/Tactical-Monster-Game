#ifndef FLOATING_H
#define FLOATING_H
#include "hexagonagents.h"
class Floating : public hexagonAgents
{
public:
    Floating();
private:
    QString Name; // Billy, Abgus, ...
    int HP;
    int mobility;
    int Damage;
    int AttackRange;
    int PlayerOwn;
};

#endif
