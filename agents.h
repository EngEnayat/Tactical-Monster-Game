#ifndef AGENTS_H
#define AGENTS_H
#include <QString>
#include "hexagonagents.h"
class Agents: public hexagonAgents
{
public:
    Agents();

private:
    QString type; // floating, grounded ...
    int HP;
    int mobility;
    int Damage;
    int AttackRange;
    int PlayerOwn;
    QString Name; // Billy, Abgus, ...
};

#endif
