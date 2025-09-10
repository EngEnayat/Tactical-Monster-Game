#include "widget.h"
#include "galleryagents.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Launching the app...";
    Widget w;
    GalleryAgents m;
    m.show();
    return a.exec();
}
