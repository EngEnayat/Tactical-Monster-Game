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

    void setProperties(int player, bool occupied, QString type);
    void getPro() const;
    void resetColor();
    int PlayerOwn() const;
    void ChangeOccupied(bool b){occupied = b;}
    bool isOccupied() const{return occupied;}
    QString HexType() const {return type;}
    void setPlacedAgent(hexagonAgents*, QString);
    hexagonAgents* getPlacedAgent() const;
    bool hasAgent() const;
    QString agentName() const;
    void addNeighbor(HexagonItems* n) {
        if (n && !neighbors.contains(n))
            neighbors.append(n);
    }

    QVector<HexagonItems*> getNeighbors() const {
        return neighbors;
    }
    void setPlayerOwn(int);
    QString getOriginalType() {return OriginalType;}
    void setOwn(int o){OriginalOwn = o;};
    int getOriginalOwn(){return OriginalOwn;}
private:
    QVector<HexagonItems*> neighbors;
    hexagonAgents *placedAgent = nullptr;
    QString type = "Unknwon"; // 1 for player 1 places, 2 for player 2, # for water, ~ for banned, " " for ground
    bool occupied = false;
    int player = 0;
    int OriginalOwn;

private:
    bool highlighted = false;
    QColor originalColor;
    QString originalPath = "";
    QString OriginalType;

public:
    void highlight(QColor color);
    void unhighlight();

    bool isHighlighted() const { return highlighted; }
};

#endif
