/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QGraphicsView *agentOne;
    QLabel *label_2;
    QGraphicsView *graphicsView;
    QGraphicsView *agentTwo;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->setEnabled(false);
        Widget->resize(1185, 724);
        Widget->setMinimumSize(QSize(1185, 724));
        Widget->setStyleSheet(QString::fromUtf8("this->setStyleSheet(\n"
"    \"QLabel {\"\n"
"    \"  background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \"\n"
"    \"              stop:0 rgb(58, 12, 163), \"\n"
"    \"              stop:0.5 rgb(98, 0, 238), \"\n"
"    \"              stop:1 rgb(144, 19, 254));\"\n"
"    \"  color: white;\"\n"
"    \"  font-size: 22px;\"\n"
"    \"  font-weight: bold;\"\n"
"    \"  padding: 10px 20px;\"\n"
"    \"  border: 2px solid rgb(255, 215, 0);\"\n"
"    \"  border-radius: 12px;\"\n"
"    \"  font-family: 'Segoe UI', 'Arial';\"\n"
"    \"  box-shadow: 0px 0px 15px rgba(255, 215, 0, 0.7);\"\n"
"    \"}\"\n"
");\n"
""));
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        agentOne = new QGraphicsView(Widget);
        agentOne->setObjectName("agentOne");
        agentOne->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(agentOne->sizePolicy().hasHeightForWidth());
        agentOne->setSizePolicy(sizePolicy);
        agentOne->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        agentOne->setStyleSheet(QString::fromUtf8("background: transparent; border: none;\n"
""));

        horizontalLayout->addWidget(agentOne);

        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        graphicsView = new QGraphicsView(Widget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setStyleSheet(QString::fromUtf8("background: transparent; border: none;"));

        horizontalLayout->addWidget(graphicsView);

        agentTwo = new QGraphicsView(Widget);
        agentTwo->setObjectName("agentTwo");
        agentTwo->setEnabled(false);
        sizePolicy.setHeightForWidth(agentTwo->sizePolicy().hasHeightForWidth());
        agentTwo->setSizePolicy(sizePolicy);
        agentTwo->setMaximumSize(QSize(16777215, 16777215));
        agentTwo->setStyleSheet(QString::fromUtf8("background: transparent; border: none;"));

        horizontalLayout->addWidget(agentTwo);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
