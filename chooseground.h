#ifndef CHOOSEGROUND_H
#define CHOOSEGROUND_H
#include <QGraphicsScene>
#include <QDialog>
#include "galleryagents.h"
#include "secondpage.h"
namespace Ui {
class ChooseGround;
}

class ChooseGround : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseGround(QWidget *parent = nullptr);
    ~ChooseGround();
    bool eventFilter(QObject *obj, QEvent *event);
    void createHexagon(qreal x, qreal y, QChar ch, QGraphicsScene *); 
    void loadHexGrid(const QString& filePath, QGraphicsScene* scene, QGraphicsView*);
    static QString playerOne;
    static QString PlayerTwo;
    
    
    
    static void setSelectedMap(const QString &name);
    static QString getSelectedMap();
private slots:
    void on_GoToGalleryButton_clicked();
    
private:
    Ui::ChooseGround *ui;
    
    const qreal hexSize = 45.0;
    const qreal hexWidth = hexSize * 2;
    const qreal hexHeight = hexSize * qSqrt(3);
    
    QGraphicsScene *scene1, *scene2, *scene3, *scene4, *scene5,
        *scene6, *scene7, *scene8;
    
    QGraphicsView* selectedView = nullptr;
    
    
    static QString selectedMapName;
    
    //object for go to the gallery agents
    GalleryAgents AgentPage;
    SecondPage backtoSecondPage;
    


};

#endif // CHOOSEGROUND_H
