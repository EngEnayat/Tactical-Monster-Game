#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPolygonItem>
#include "hexagonitems.h"
#include <QMouseEvent>
#include <QGraphicsView>
#include "hexagonagents.h"
#include "hexagonitems.h"
#include <QLabel>
#include <QGraphicsRectItem>
#include <QObject>

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
    Widget(QStringList PlayerOneSelectedAgents = QStringList(),QStringList PlayerTwoSelectedAgents = QStringList(),QWidget *parent = nullptr);
    ~Widget();
    bool eventFilter(QObject *obj, QEvent *event);
    HexagonItems* getHexagonAtPosition(const QPointF &pos);
    QPixmap getCircularPixmap(const QPixmap &src, int size);
    hexagonAgents* getAgentHexagonAtPosition(const QPointF &pos, QGraphicsView*);
    void addAgentToggleButton();
    void HoverAgents(QPointF, int);

    void SetPropertiesAgents(QVector<hexagonAgents*>);

    bool CheckAttack(HexagonItems*);

    void MovingAgent(HexagonItems *);

    int PlayerOneDeletedAgents = 6;
    int PlayerTwoDeletedAgents = 6;

    void Vectory();

private:
    QGraphicsScene *Scence ;
    HexagonItems* lastHoveredHex = nullptr;

    QGraphicsScene* scene;
    const qreal hexWidth = 80;
    const qreal hexHeight = 69.4;
    Ui::Widget *ui;
    QMap<QPair<int, int>, HexagonItems*> hexMap;

    QMap<QPair<int, int>, hexagonAgents*> Player1;
    void LoadingAgents(QGraphicsView *, QStringList);

    QList<hexagonAgents*> agentHexList;
    QVector<hexagonAgents*> agentsOne;
    QVector<hexagonAgents*> agentsTwo;
    static int PlayerTurn ;
    void HoverHexagon(QPointF);
    void ClickHexagon(QPointF);

    QVector<hexagonAgents*> activeAgents;

    static int DroppedCount;
    void BFS(HexagonItems*, int );
    void AddHexNeighbor();
    void ReplaceAgent(HexagonItems*);
private:
    QGraphicsProxyWidget* hoverInfoProxy[2] = {nullptr, nullptr}; // index 0 = player 1, index 1 = player 2
    QLabel* hoverLabel[2] = {nullptr, nullptr};

    HexagonItems* lastClickedHex = nullptr;
    QVector<HexagonItems*> lastVisited;
    QVector<HexagonItems*> InAttackRange;
    void SetEnemyRange();

};


class ClickableRect : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    explicit ClickableRect(qreal x, qreal y, qreal w, qreal h, QObject* parent = nullptr)
        : QObject(parent), QGraphicsRectItem(x, y, w, h)
    {
        setAcceptHoverEvents(true); // Accept hover events
        setCursor(Qt::PointingHandCursor); // Change cursor on hover
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable); // Allow selection and focus
    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;

signals:
    void clicked();
};


#endif
