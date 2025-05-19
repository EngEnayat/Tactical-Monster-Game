#include "widget.h"

#include <QApplication>
<<<<<<< HEAD
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Launching the app...";
=======

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
>>>>>>> d860567a9f431f0d31d092f380ceb9e0905486fc
    Widget w;
    w.show();
    return a.exec();
}
