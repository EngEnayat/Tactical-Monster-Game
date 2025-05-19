#include "agentitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

AgentItem::AgentItem(const QPixmap &pixmap, int index)
    : m_pixmap(pixmap), m_index(index)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);  // Important!
}

QRectF AgentItem::boundingRect() const
{
    return QRectF(0, 0, m_pixmap.width(), m_pixmap.height());
}

void AgentItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, m_pixmap);
}

void AgentItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(m_index);
}

void AgentItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    emit hovered(m_index);
}

void AgentItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    emit unhovered(m_index);
}
