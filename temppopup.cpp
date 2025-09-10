#include "temppopup.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>

TempPopup::TempPopup(const QString &text, QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(text, this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("QLabel { background-color: white; color: black; font-size: 20px; border-radius: 10px; padding: 10px; }");
    layout->addWidget(label);
    setLayout(layout);
    resize(200, 100);

    QTimer::singleShot(2000, this, &QWidget::close);
}
