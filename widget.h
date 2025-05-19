#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPolygonItem>
#include "hexagonitems.h"
#include <QMouseEvent>
#include "clickablepixmapitem.h"
#include <QGraphicsView>
#include "hexagonagents.h"
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
    void setBackground();
    QPixmap getCircularPixmap(const QPixmap &src, int size);
    hexagonAgents* getAgentHexagonAtPosition(const QPointF &pos);
    void addAgentToggleButton();
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

    void LoadingAgents(QGraphicsView *);
    QList<hexagonAgents*> agentHexList;
    bool agentHidden1 = false;
    bool agentHidden2 = false;
    QVector<hexagonAgents*> agentsOne;
    QVector<hexagonAgents*> agentsTwo;
    int turn;
private slots:

};
#endif
