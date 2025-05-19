#include "clickablepixmapitem.h"
#include <QGraphicsSceneMouseEvent>

ClickablePixmapItem::ClickablePixmapItem(const QPixmap &pixmap, int agentIndex, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(pixmap, parent), m_agentIndex(agentIndex)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    setEnabled(true);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setAcceptHoverEvents(true);
}

void ClickablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();  // Explicitly accept the event
    emit clicked(m_agentIndex);
    qDebug() << "Clicked agent:" << m_agentIndex;
}
