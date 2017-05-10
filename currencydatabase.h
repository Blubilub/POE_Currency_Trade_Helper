#ifndef CURRENCYDATABASE_H
#define CURRENCYDATABASE_H
#include "includes.h"
#include <QString>

class CurrencyDatabase
{
public:
    CurrencyDatabase();
    static QString formatDataForDB(const buyAndSellVal* val);
};

#endif // CURRENCYDATABASE_H
