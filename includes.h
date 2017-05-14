#ifndef INCLUDES_H
#define INCLUDES_H
#include <QLabel>
#include <QPushButton>
#include <QString>

struct buyAndSellVal {
    float youBuy;
    float youSell;
};

struct tradeDescription {
    QLabel *label;
    QPushButton *button;
    QString link;
    QString name;
};

#endif // INCLUDES_H
