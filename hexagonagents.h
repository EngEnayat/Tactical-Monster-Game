#ifndef HEXAGONAGENTS_H
#define HEXAGONAGENTS_H

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QPixmap>
#include <cmath>
#include <QPainter>
#include "agents.h"

class hexagonAgents : public QObject, public QGraphicsPolygonItem {
    QPixmap pix;
    Q_OBJECT;
public:
    hexagonAgents(qreal size, const QString& imagePath, QGraphicsItem* parent = nullptr)
        : QGraphicsPolygonItem(parent), pix(imagePath)
    {
        QPolygonF hexagon;
        for (int i = 0; i < 6; ++i) {
            qreal angle_deg = 60 * i - 30;
            qreal angle_rad = M_PI / 180 * angle_deg;
            qreal x = size * cos(angle_rad);
            qreal y = size * sin(angle_rad);
            hexagon << QPointF(x, y);
        }
        setPolygon(hexagon);

        if (imagePath == "f")
            this->setBrush(QColor(44,139,33));
        setPen(QPen(Qt::black, 1));
        this->setVisible(false);
    }

    void HideAgents(bool, QVector<hexagonAgents*>);
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override
    {
        painter->setPen(pen());

        QPainterPath path;
        path.addPolygon(polygon());
        path.closeSubpath();

        painter->setClipPath(path);

        painter->drawPixmap(boundingRect().toRect(), pix);

        painter->setClipping(false);

        painter->drawPolygon(polygon());
    }
private:
    QMap<QPair<int,int>, Agents*> PlayerOneAgents;
    QMap<QPair<int,int>, Agents*> PlayerTwoAgents;
    static hexagonAgents *SelectedAgents;
};
#endif
