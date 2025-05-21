#ifndef GALLERYAGENTS_H
#define GALLERYAGENTS_H

#include <QWidget>
#include <QPushButton>
namespace Ui {
class GalleryAgents;
}

class GalleryAgents : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryAgents(QWidget *parent = nullptr);
    ~GalleryAgents();
    void setButtonImage(QPushButton* button, const QString& imagePath);
private slots:
    void on_Kabu_clicked();
    void showProperties(int hp,int mobility,QString type,int damage, int attackRange, QString name, QString path);

private:
    Ui::GalleryAgents *ui;
};

#endif // GALLERYAGENTS_H
