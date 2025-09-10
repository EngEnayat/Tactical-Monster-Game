// winnerpage.h
#ifndef WINNERPAGE_H
#define WINNERPAGE_H

#include <QWidget>

class WinnerPage : public QWidget {
    Q_OBJECT
public:
    explicit WinnerPage(const QString &winnerName, QWidget *parent = nullptr);
};

#endif
