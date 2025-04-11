#ifndef GALLERY_H
#define GALLERY_H

#include <QDialog>

namespace Ui {
class Gallery;
}

class Gallery : public QDialog
{
    Q_OBJECT

public:
    explicit Gallery(QWidget *parent = nullptr);
    ~Gallery();

private:
    Ui::Gallery *ui;
};

#endif // GALLERY_H
