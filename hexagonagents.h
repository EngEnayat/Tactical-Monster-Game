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
    explicit hexagonAgents(qreal size, const QString& imagePath, QGraphicsItem* parent = nullptr);
    static hexagonAgents* getSelectedAgent();
    void HideAgents(bool, QVector<hexagonAgents*>);
    void StoreAddress(QPointF, QString);
    QString getAgentAddress(QPointF);
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
    QMap<QPair<int,int>, QString> HexAddress;
    QMap<QPair<int,int>, Agents*> PlayerOneAgents;
    QMap<QPair<int,int>, Agents*> PlayerTwoAgents;
    static hexagonAgents *SelectedAgents;
};

#endif
