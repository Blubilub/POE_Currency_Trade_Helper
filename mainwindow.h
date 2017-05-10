#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "websiteparser.h"
#include "includes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WebsiteParser* wp[30];
    QString formatRatiosForLabel(QList<buyAndSellVal> val, int view = 1);
    QString linkList[30];

private slots:
    void pushButtonAltClicked();
    void pushButtonFusClicked();
    void pushButtonExaClicked();
    void pushButtonAlcClicked();
    void pushButtonGCPClicked();
    void pushButtonChrClicked();
    void pushButtonJewClicked();
    void pushButtonChaClicked();
    void pushButtonChiClicked();
    void pushButtonScoClicked();
    void pushButtonBleClicked();
    void pushButtonRegClicked();
    void pushButtonDivClicked();
    void pushButtonVaaClicked();
    void pushButtonBauClicked();
    void downloadClicked();
    void parseWebsiteSource(QNetworkReply* reply, int wpID);

};

#endif // MAINWINDOW_H
