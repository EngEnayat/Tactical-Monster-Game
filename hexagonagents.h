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
    explicit hexagonAgents(qreal size =0 , const QString& imagePath = "",QGraphicsItem* parent = nullptr);
    static hexagonAgents* getSelectedAgent();
    void AgentClicked(QVector<hexagonAgents*>);
    static QString ImagePath(QString);

    void setDropped(bool b){IsDropped = b;}
    void CleanSelection();
    void ChangePlayer();
    static int PlayerTurn();
    void InActive( QVector<hexagonAgents*>);
    void EnableAll(QVector<hexagonAgents*>);

    void SetType(QString);  // set its type Grounded, WATER, ...
    QString getType();

    static void getSelectedAgents();
    virtual ~hexagonAgents() override {delete SelectedAgents;}
    void SetName(QString);
    QString GetName();
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
    QString Name;
    QString Type; // Floating, Grounded, Water Walking, Flying
    static int CurrentPlayer;
    bool IsDropped = false;
    static hexagonAgents *SelectedAgents;
    static QMap<QString, QString> nameToFilename ;

public:
    static QStringList GroundedList;
    static QStringList WaterAgentsList;
    static QStringList FloatingList;
    static QStringList FlyingList;

public:
    int GetHp(){return 0;};
    int GetMobility(){return 0;};
    int getDamage(){return 0;};
    int GetAttackRange(){return 0;};
    int GetPlayerOwn(){return 0;};
};

#endif
