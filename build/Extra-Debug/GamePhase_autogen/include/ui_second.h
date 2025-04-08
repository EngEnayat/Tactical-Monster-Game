/********************************************************************************
** Form generated from reading UI file 'second.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECOND_H
#define UI_SECOND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_second
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pvpMatch;
    QPushButton *pvpGame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *second)
    {
        if (second->objectName().isEmpty())
            second->setObjectName("second");
        second->resize(800, 600);
        centralwidget = new QWidget(second);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 10, 661, 511));
        label->setStyleSheet(QString::fromUtf8("image: url(:/second.jpg);"));
        pvpMatch = new QPushButton(centralwidget);
        pvpMatch->setObjectName("pvpMatch");
        pvpMatch->setGeometry(QRect(510, 300, 191, 26));
        pvpMatch->setStyleSheet(QString::fromUtf8("border-top-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(255, 255, 255, 255), stop:0.373979 rgba(255, 255, 255, 255), stop:0.373991 rgba(33, 30, 255, 255), stop:0.624018 rgba(33, 30, 255, 255), stop:0.624043 rgba(255, 0, 0, 255), stop:1 rgba(255, 0, 0, 255));\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(237, 51, 59);"));
        pvpGame = new QPushButton(centralwidget);
        pvpGame->setObjectName("pvpGame");
        pvpGame->setGeometry(QRect(507, 370, 191, 26));
        pvpGame->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color: rgb(246, 97, 81);"));
        second->setCentralWidget(centralwidget);
        menubar = new QMenuBar(second);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        second->setMenuBar(menubar);
        statusbar = new QStatusBar(second);
        statusbar->setObjectName("statusbar");
        second->setStatusBar(statusbar);

        retranslateUi(second);

        QMetaObject::connectSlotsByName(second);
    } // setupUi

    void retranslateUi(QMainWindow *second)
    {
        second->setWindowTitle(QCoreApplication::translate("second", "MainWindow", nullptr));
        label->setText(QString());
        pvpMatch->setText(QCoreApplication::translate("second", "Start a sync PVP match", nullptr));
        pvpGame->setText(QCoreApplication::translate("second", "Start a sync PVP game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class second: public Ui_second {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECOND_H
