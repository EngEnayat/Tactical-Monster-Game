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
    Q_OBJECT
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
    virtual ~hexagonAgents() = default;
    void SetName(QString);
    QString GetName();
    void SetAttackCheck(bool var);
    bool getAttackCheck();
    virtual bool WaterMoving() = 0;
    virtual bool GroundMoving() = 0;
    virtual bool BannedMoving() = 0;
    virtual bool CanStayGround() = 0;
    virtual bool CanStayWater() = 0;
    virtual bool canStayBanned() = 0;
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

    bool isAttackRange = false; // for checking the attack condition

public:
    static QStringList GroundedList;
    static QStringList WaterAgentsList;
    static QStringList FloatingList;
    static QStringList FlyingList;

public:
    virtual void setHP(int hp) = 0;
    virtual void setMobility(int m) = 0;
    virtual void setDamage(int d) = 0;
    virtual void setAttackRange(int r) = 0;
    virtual void setPlayerOwn(int p) = 0;
    virtual int GetHp() const = 0;
    virtual int GetMobility() const = 0;
    virtual int getDamage() const = 0;
    virtual int GetAttackRange() const = 0;
    virtual int GetPlayerOwn() const = 0;
    virtual QString getAgentType() const = 0;
};

#endif
