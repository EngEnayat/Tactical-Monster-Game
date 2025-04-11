#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "second.h"
#include "gallery.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    second *s;
    Gallery *g;
};
#endif // WIDGET_H
