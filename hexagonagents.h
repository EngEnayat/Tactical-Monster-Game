#ifndef HEXAGONAGENTS_H
#define HEXAGONAGENTS_H

#include <QGraphicsPolygonItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QPixmap>
#include <cmath>
#include <QPainter>
class hexagonAgents : public QObject, public QGraphicsPolygonItem {
    QPixmap pix;
    Q_OBJECT;
public:
    explicit hexagonAgents(qreal size =0 , const QString& imagePath = "", QGraphicsItem* parent = nullptr);
    static hexagonAgents* getSelectedAgent();
    void HideAgents(QVector<hexagonAgents*>);
    void StoreAddress(QPointF, QString);
    QString getAgentAddress(QPointF);
    void setDropped(bool b){IsDropped = b;}
    void CleanSelection();
    void ChangePlayer();
    static int PlayerTurn();
    void InActive( QVector<hexagonAgents*>);
    void EnableAll(QVector<hexagonAgents*>);
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
    static int CurrentPlayer;
    bool IsDropped = false;
    QMap<QPair<int,int>, QString> HexAddress;
    static hexagonAgents *SelectedAgents;
};

#endif
