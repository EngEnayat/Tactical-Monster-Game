#ifndef TEMPPOPUP_H
#define TEMPPOPUP_H

#include <QWidget>

class TempPopup : public QWidget {
    Q_OBJECT
public:
    explicit TempPopup(const QString &text, QWidget *parent = nullptr);
};

#endif
