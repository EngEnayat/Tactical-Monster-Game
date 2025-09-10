#include "winnerpage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QScreen>

WinnerPage::WinnerPage(const QString &winnerName, QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    resize(400, 250);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *title = new QLabel("🎉 Congratulations! 🎉", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: gold;");

    QLabel *winnerLabel = new QLabel(QString("Winner: %1").arg(winnerName), this);
    winnerLabel->setAlignment(Qt::AlignCenter);
    winnerLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: white;");

    QPushButton *okBtn = new QPushButton("OK", this);
    okBtn->setFixedSize(100, 40);
    okBtn->setStyleSheet("QPushButton { background-color: #444; color: white; border-radius: 8px; }"
                         "QPushButton:hover { background-color: #666; }");
    connect(okBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(winnerLabel);
    layout->addStretch();
    layout->addWidget(okBtn, 0, Qt::AlignCenter);

    setLayout(layout);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int x = screenGeometry.center().x() - width() / 2;
    int y = screenGeometry.center().y() - height() / 2;
    move(x, y);
}
