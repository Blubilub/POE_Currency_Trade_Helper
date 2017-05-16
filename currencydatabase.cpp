#include "currencydatabase.h"
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <iostream>


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


void CurrencyDatabase::writeToDB(const QList<buyAndSellVal> *write, const QString dbName){
    QString dbData;
    QFile database("database/" + dbName);
    if (!database.exists()) {
        QTextStream out(&database);
        out << "date,youSell,youBuy\n";
    }
    QString errMsg;
    QFileDevice::FileError err = QFileDevice::NoError;
    if(!database.open(QIODevice::WriteOnly | QIODevice::Append)) {
        std::cerr << "DATABASE DOESNT EXIST" << std::endl;
        err = database.error();
        //ui->textBrowser->append(errMsg);
        emit output(&errMsg);
        return;
    }
    for(int i = 0; i<5 && i<write->size(); i++){
        dbData = formatDataForDB(&write->at(i));
        QTextStream out(&database);
        out << dbData;
    }
    database.close();
}
