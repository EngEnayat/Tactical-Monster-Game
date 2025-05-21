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
    void AddAddress(QString name, int Player);
private slots:
    void on_Kabu_clicked();
    void showProperties(int hp,int mobility,QString type,int damage, int attackRange, QString name, QString path);

    void on_StartButton_clicked();

private:
    QMap<QString, QString> nameToFilename = {
        {"Sir Lamorak", "Lamorak"},
        {"Eloi", "Eloi (1)"},
        {"Sir Philip", "Sir philiph"},
        {"Frust", "Frost"},
        {"Death", "death"},
        {"Rambu", "Rambo"},
        {"Colonel Baba", "Colonel_baba"}
    };

    Ui::GalleryAgents *ui;
    QStringList PlayerOneAgents;
    QStringList PlayerTwoAgents;
    static int agentCount;
    QStringList PlayerOneImages;
    QStringList PlayerTwoImages;
};

#endif
