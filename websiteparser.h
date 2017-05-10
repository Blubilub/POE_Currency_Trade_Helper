#ifndef WEBSITEPARSER_H
#define WEBSITEPARSER_H
#include <QtNetwork>
#include <iostream>
#include <QObject>
#include "includes.h"

class WebsiteParser : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager *manager;
    int wpID;

public:
    WebsiteParser(int id);
    void getWebsite(QString website);
    static QList<buyAndSellVal> getBuyAndSellVal(QString reply);
    int writeToFile(QList<buyAndSellVal>);

private slots:
    void result(QNetworkReply *tReply);

signals:
    finishedDownloading(QNetworkReply*, int);
};

#endif // WEBSITEPARSER_H
