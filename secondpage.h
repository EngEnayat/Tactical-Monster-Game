#ifndef SECONDPAGE_H
#define SECONDPAGE_H
#include "galleryagents.h"
#include <QDialog>


namespace Ui {
class SecondPage;
}

class SecondPage : public QDialog
{
    Q_OBJECT

public:
    explicit SecondPage(QWidget *parent = nullptr);
    void startSecond();
    static void savePlayer1Name(const QString &name1);
    static void savePlayer2Name(const QString &name2);
    static QString getPlayer1Name();
    static QString getPlayer2Name();
    
    friend class GalleryAgents;
    static bool onNameButtonClicked;
    static bool NameButtonClicked;
   
    ~SecondPage();
    
private slots:
    void on_Agents_clicked();
    
    void on_getNameButton_clicked();
    
private:
    Ui::SecondPage *ui;
    GalleryAgents agentsPage;
    static QString player1Name;
    static QString player2Name;

    
    
};

#endif // SECONDPAGE_H
