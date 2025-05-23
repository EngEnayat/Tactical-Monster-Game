#ifndef HEXAGONITEMS_H
#define HEXAGONITEMS_H
#include <QPolygonF>
#include <QGraphicsPolygonItem>
#include "hexagonagents.h"

class HexagonItems : public QGraphicsPolygonItem {
public:
    HexagonItems(const QPolygonF& polygon, int row, int col);

    int row;
    int col;

    void setProperties(int player, bool occupied, char type);
    void getPro() const;
    void resetColor();
    int PlayerOwn() const;
    void ChangeOccupied(bool b){occupied = b;}
    bool isOccupied() const{return occupied;}
    char HexType() const {return type;}
    void setPlacedAgent(hexagonAgents*);
    hexagonAgents* getPlacedAgent() const;
    bool hasAgent() const;
    QString agentName() const;
private:
    hexagonAgents *placedAgent = nullptr;
    char type = '\0';
    bool occupied = false;
    int player = 0;
};

#endif
