#ifndef INCLUDES_H
#define INCLUDES_H
#include <QLabel>
#include <QPushButton>
#include <QString>
//#include <websiteparser.h>

struct buyAndSellVal {
    float youBuy;
    float youSell;
};

class WebsiteParser;

struct tradeDescription {
    QLabel *label;
    QPushButton *button;
    WebsiteParser *websiteParser;
    QString link;
    QString name;
};

#endif // INCLUDES_H
