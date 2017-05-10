#include "websiteparser.h"

WebsiteParser::WebsiteParser(int id) {
    wpID = id;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(result(QNetworkReply*)));
}


void WebsiteParser::getWebsite(QString website) {
    manager->get(QNetworkRequest(QUrl(website)));

}


QList<buyAndSellVal> WebsiteParser::getBuyAndSellVal(QString reply) {
    QList<buyAndSellVal> val;
    buyAndSellVal tempBuyAndSellVal;

    int currentIndex = 0;
    int startIndex = reply.indexOf("data-sellvalue=");
    int i = 0;
    while(true) {
        if(startIndex == reply.indexOf("data-sellvalue=", currentIndex) && currentIndex != 0 || i>=25) {
            break;
        }
        int startIndexSellVal = reply.indexOf("data-sellvalue=", currentIndex);
        int endIndexSellVal = reply.indexOf("\"", startIndexSellVal+16);
        tempBuyAndSellVal.youSell = reply.mid(startIndexSellVal+16, endIndexSellVal - (startIndexSellVal+16)).toFloat();
        int startIndexBuyVal = reply.indexOf("data-buyvalue=", currentIndex);
        int endIndexBuyVal = reply.indexOf("\"", startIndexBuyVal+15);
        tempBuyAndSellVal.youBuy = reply.mid(startIndexBuyVal+15, endIndexBuyVal - (startIndexBuyVal+15)).toFloat();
        if(endIndexBuyVal == -1) {
            break;
        }
        val.append(tempBuyAndSellVal);
        currentIndex = endIndexBuyVal+1;
        i++;
    }
    return val;
}


int WebsiteParser::writeToFile(QList<buyAndSellVal>) {

}


void WebsiteParser::result(QNetworkReply *tReply) {
    emit finishedDownloading(tReply, wpID);
}
