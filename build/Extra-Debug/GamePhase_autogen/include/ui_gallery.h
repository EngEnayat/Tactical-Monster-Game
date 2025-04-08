/********************************************************************************
** Form generated from reading UI file 'gallery.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GALLERY_H
#define UI_GALLERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gallery
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Gallery)
    {
        if (Gallery->objectName().isEmpty())
            Gallery->setObjectName("Gallery");
        Gallery->resize(404, 358);
        centralwidget = new QWidget(Gallery);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 341, 301));
        label->setStyleSheet(QString::fromUtf8("image: url(:/galler.jpeg);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(70, 50, 88, 26));
        Gallery->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Gallery);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 404, 23));
        Gallery->setMenuBar(menubar);
        statusbar = new QStatusBar(Gallery);
        statusbar->setObjectName("statusbar");
        Gallery->setStatusBar(statusbar);

        retranslateUi(Gallery);

        QMetaObject::connectSlotsByName(Gallery);
    } // setupUi

    void retranslateUi(QMainWindow *Gallery)
    {
        Gallery->setWindowTitle(QCoreApplication::translate("Gallery", "MainWindow", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("Gallery", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gallery: public Ui_Gallery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GALLERY_H
