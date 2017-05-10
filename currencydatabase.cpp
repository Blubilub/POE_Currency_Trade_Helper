#include "currencydatabase.h"
#include <QTime>

CurrencyDatabase::CurrencyDatabase()
{

}


QString CurrencyDatabase::formatDataForDB(const buyAndSellVal *val) {
    QString currentDate = QDate::currentDate().toString("yyyy.MM.dd");
    QString currentTime = QTime::currentTime().toString("hh.mm.ss");
    QString retValue = currentDate + "." + currentTime + "," +
                       //QString::number(val->youSell/val->youBuy) + "," +      //ratio not needed yet
                       QString::number(val->youBuy) + "," +
                       QString::number(val->youSell) + "\n";
    //QString::number(val->youSell);

    return retValue;
}
