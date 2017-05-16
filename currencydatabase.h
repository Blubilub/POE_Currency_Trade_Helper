#ifndef CURRENCYDATABASE_H
#define CURRENCYDATABASE_H
#include "includes.h"
#include <QString>
#include <QObject>

class CurrencyDatabase : public QObject {
    Q_OBJECT
public:
    CurrencyDatabase();
    static QString formatDataForDB(const buyAndSellVal* val);
    static void writeToDB(const QList<buyAndSellVal> *write, const QString dbName);

signals:
    void output(const QString*);
};

#endif // CURRENCYDATABASE_H
