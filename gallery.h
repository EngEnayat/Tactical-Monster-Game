#ifndef GALLERY_H
#define GALLERY_H

#include <QMainWindow>

namespace Ui {
class Gallery;
}

class Gallery : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gallery(QWidget *parent = nullptr);
    ~Gallery();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Gallery *ui;
};

#endif // GALLERY_H
