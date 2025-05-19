// clickablepixmapitem.h
#ifndef CLICKABLEPIXMAPITEM_H
#define CLICKABLEPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class ClickablePixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit ClickablePixmapItem(const QPixmap &pixmap, int agentIndex, QGraphicsItem *parent = nullptr);

signals:
    void clicked(int agentIndex);

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_agentIndex;
};

#endif
