#ifndef HEXAGONITEMS_H
#define HEXAGONITEMS_H
#include <QPolygonF>
#include <QGraphicsPolygonItem>


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

private:
    char type = '\0';
    bool occupied = false;
    int player = 0;
};

#endif
