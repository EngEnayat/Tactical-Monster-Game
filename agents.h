#ifndef AGENTS_H
#define AGENTS_H
#include <QString>
#include "QGraphicsPixmapItem"
class Agents: public QGraphicsPixmapItem
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
