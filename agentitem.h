#ifndef AGENTITEM_H
#define AGENTITEM_H

#include <QGraphicsObject>
#include <QPixmap>

class AgentItem : public QGraphicsObject
{
    Q_OBJECT
public:
    AgentItem(const QPixmap &pixmap, int index);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

signals:
    void clicked(int index);
    void hovered(int index);
    void unhovered(int index);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QPixmap m_pixmap;
    int m_index;
};

#endif // AGENTITEM_H
