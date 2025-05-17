#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPolygonItem>
#include "hexagonitems.h"
#include <QMouseEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    void createHexagon(qreal x, qreal y, QChar ch, int row, int col);
    QPair<int, int> convertScenePosToGrid(const QPointF& pos);
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool eventFilter(QObject *obj, QEvent *event);
    HexagonItems* getHexagonAtPosition(const QPointF &pos);
private:
    HexagonItems* lastHoveredHex = nullptr;

    QGraphicsPolygonItem *top;
    QGraphicsPolygonItem *topLeft;
    QGraphicsPolygonItem topRight;
    QGraphicsPolygonItem *buttom;
    QGraphicsPolygonItem *buttomLeft;
    QGraphicsPolygonItem *buttomRight;
    QGraphicsScene* scene;
    const qreal hexWidth = 80;
    const qreal hexHeight = 69.4;
    Ui::Widget *ui;
    QMap<QPair<int, int>, HexagonItems*> hexMap;

};
#endif
