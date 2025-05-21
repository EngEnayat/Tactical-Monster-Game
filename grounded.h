#ifndef GROUNDED_H
#define GROUNDED_H
#include "hexagonagents.h"
class Grounded : public hexagonAgents
{
public:
    Grounded();
private:
    QString Name; // Billy, Abgus, ...
    int HP;
    int mobility;
    int Damage;
    int AttackRange;
    int PlayerOwn;
};

#endif
