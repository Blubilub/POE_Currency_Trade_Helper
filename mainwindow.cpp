#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFile>
#include <QIODevice>
#include "currencydatabase.h"
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtonAlteration, SIGNAL(clicked(bool)), this, SLOT(pushButtonAltClicked()));
    connect(ui->pushButtonFusing, SIGNAL(clicked(bool)), this, SLOT(pushButtonFusClicked()));
    connect(ui->pushButtonExalted, SIGNAL(clicked(bool)), this, SLOT(pushButtonExaClicked()));
    connect(ui->pushButtonAlchemy, SIGNAL(clicked(bool)), this, SLOT(pushButtonAlcClicked()));
    connect(ui->pushButtonGemcutters, SIGNAL(clicked(bool)), this, SLOT(pushButtonGCPClicked()));
    connect(ui->pushButtonChromatic, SIGNAL(clicked(bool)), this, SLOT(pushButtonChrClicked()));
    connect(ui->pushButtonJewellers, SIGNAL(clicked(bool)), this, SLOT(pushButtonJewClicked()));
    connect(ui->pushButtonChance, SIGNAL(clicked(bool)), this, SLOT(pushButtonChaClicked()));
    connect(ui->pushButtonChisel, SIGNAL(clicked(bool)), this, SLOT(pushButtonChiClicked()));
    connect(ui->pushButtonScouring, SIGNAL(clicked(bool)), this, SLOT(pushButtonScoClicked()));
    connect(ui->pushButtonBlessed, SIGNAL(clicked(bool)), this, SLOT(pushButtonBleClicked()));
    connect(ui->pushButtonRegret, SIGNAL(clicked(bool)), this, SLOT(pushButtonRegClicked()));
    connect(ui->pushButtonDivine, SIGNAL(clicked(bool)), this, SLOT(pushButtonDivClicked()));
    connect(ui->pushButtonVaal, SIGNAL(clicked(bool)), this, SLOT(pushButtonVaaClicked()));
    connect(ui->pushButtonBauble, SIGNAL(clicked(bool)), this, SLOT(pushButtonBauClicked()));
    connect(ui->pushButtonDownload, SIGNAL(clicked(bool)), this, SLOT(downloadClicked()));

    for(int i = 0; i < 30; i++) {
        tradeDescriptionList[i].websiteParser = new WebsiteParser(i);
        //wp[i] = new WebsiteParser(i);
        connect(tradeDescriptionList[i].websiteParser, SIGNAL(finishedDownloading(QNetworkReply*, int)), this, SLOT(parseWebsiteSource(QNetworkReply*, int)));
    }
    tradeDescriptionList[0].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=1&have=4";  //alt->c  x
    tradeDescriptionList[1].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=1";  //c->alt  c
    tradeDescriptionList[2].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=2";  //fus->c  x
    tradeDescriptionList[3].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=2&have=4";  //c->fus  c
    tradeDescriptionList[4].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=6";  //exa->c  x
    tradeDescriptionList[5].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=6&have=4";  //c->exa  c
    tradeDescriptionList[6].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=3";  //alc->c  x
    tradeDescriptionList[7].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=3&have=4";  //c->alc  c
    tradeDescriptionList[8].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=5";  //gcp->c  x
    tradeDescriptionList[9].link  = "http://currency.poe.trade/search?league=Standard&online=x&want=5&have=4";  //c->gcp  c
    tradeDescriptionList[10].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=7";  //chr->c  x
    tradeDescriptionList[11].link = "http://currency.poe.trade/search?league=Standard&online=x&want=7&have=4";  //c->chr  c
    tradeDescriptionList[12].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=8";  //jew->c  x
    tradeDescriptionList[13].link = "http://currency.poe.trade/search?league=Standard&online=x&want=8&have=4";  //c->jew  c
    tradeDescriptionList[14].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=9";  //cha->c  x
    tradeDescriptionList[15].link = "http://currency.poe.trade/search?league=Standard&online=x&want=9&have=4";  //c->cha  c
    tradeDescriptionList[16].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=10"; //chi->c  x
    tradeDescriptionList[17].link = "http://currency.poe.trade/search?league=Standard&online=x&want=10&have=4"; //c->chi  c
    tradeDescriptionList[18].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=11"; //sco->c  x
    tradeDescriptionList[19].link = "http://currency.poe.trade/search?league=Standard&online=x&want=11&have=4"; //c->sco  c
    tradeDescriptionList[20].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=12"; //ble->c  x
    tradeDescriptionList[21].link = "http://currency.poe.trade/search?league=Standard&online=x&want=12&have=4"; //c->ble  c
    tradeDescriptionList[22].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=13"; //reg->c  x
    tradeDescriptionList[23].link = "http://currency.poe.trade/search?league=Standard&online=x&want=13&have=4"; //c->reg  c
    tradeDescriptionList[24].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=15"; //div->c  x
    tradeDescriptionList[25].link = "http://currency.poe.trade/search?league=Standard&online=x&want=15&have=4"; //c->div  c
    tradeDescriptionList[26].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=16"; //vaa->c  x
    tradeDescriptionList[27].link = "http://currency.poe.trade/search?league=Standard&online=x&want=16&have=4"; //c->vaa  c
    tradeDescriptionList[28].link = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=21"; //bau->c  x
    tradeDescriptionList[29].link = "http://currency.poe.trade/search?league=Standard&online=x&want=21&have=4"; //c->bau  c


    tradeDescriptionList[0].label = ui->labelAltToCao;
    tradeDescriptionList[1].label = ui->labelCaoToAlt;
    tradeDescriptionList[2].label = ui->labelFusToCao;
    tradeDescriptionList[3].label = ui->labelCaoToFus;
    tradeDescriptionList[4].label = ui->labelExaToCao;
    tradeDescriptionList[5].label = ui->labelCaoToExa;
    tradeDescriptionList[6].label = ui->labelAlcToCao;
    tradeDescriptionList[7].label = ui->labelCaoToAlc;
    tradeDescriptionList[8].label = ui->labelGCPToCao;
    tradeDescriptionList[9].label = ui->labelCaoToGCP;
    tradeDescriptionList[10].label = ui->labelChrToCao;
    tradeDescriptionList[11].label = ui->labelCaoToChr;
    tradeDescriptionList[12].label = ui->labelJewToCao;
    tradeDescriptionList[13].label = ui->labelCaoToJew;
    tradeDescriptionList[14].label = ui->labelChaToCao;
    tradeDescriptionList[15].label = ui->labelCaoToCha;
    tradeDescriptionList[16].label = ui->labelChiToCao;
    tradeDescriptionList[17].label = ui->labelCaoToChi;
    tradeDescriptionList[18].label = ui->labelScoToCao;
    tradeDescriptionList[19].label = ui->labelCaoToSco;
    tradeDescriptionList[20].label = ui->labelBleToCao;
    tradeDescriptionList[21].label = ui->labelCaoToBle;
    tradeDescriptionList[22].label = ui->labelRegToCao;
    tradeDescriptionList[23].label = ui->labelCaoToReg;
    tradeDescriptionList[24].label = ui->labelDivToCao;
    tradeDescriptionList[25].label = ui->labelCaoToDiv;
    tradeDescriptionList[26].label = ui->labelVaaToCao;
    tradeDescriptionList[27].label = ui->labelCaoToVaa;
    tradeDescriptionList[28].label = ui->labelBauToCao;
    tradeDescriptionList[29].label = ui->labelCaoToBau;

    tradeDescriptionList[0].name = "AltToCao";
    tradeDescriptionList[1].name = "CaoToAlt";
    tradeDescriptionList[2].name = "FusToCao";
    tradeDescriptionList[3].name = "CaoToFus";
    tradeDescriptionList[4].name = "ExaToCao";
    tradeDescriptionList[5].name = "CaoToExa";
    tradeDescriptionList[6].name = "AlcToCao";
    tradeDescriptionList[7].name = "CaoToAlc";
    tradeDescriptionList[8].name = "GCPToCao";
    tradeDescriptionList[9].name = "CaoToGCP";
    tradeDescriptionList[10].name = "ChrToCao";
    tradeDescriptionList[11].name = "CaoToChr";
    tradeDescriptionList[12].name = "JewToCao";
    tradeDescriptionList[13].name = "CaoToJew";
    tradeDescriptionList[14].name = "ChaToCao";
    tradeDescriptionList[15].name = "CaoToCha";
    tradeDescriptionList[16].name = "ChiToCao";
    tradeDescriptionList[17].name = "CaoToChi";
    tradeDescriptionList[18].name = "ScoToCao";
    tradeDescriptionList[19].name = "CaoToSco";
    tradeDescriptionList[20].name = "BleToCao";
    tradeDescriptionList[21].name = "CaoToBle";
    tradeDescriptionList[22].name = "RegToCao";
    tradeDescriptionList[23].name = "CaoToReg";
    tradeDescriptionList[24].name = "DivToCao";
    tradeDescriptionList[25].name = "CaoToDiv";
    tradeDescriptionList[26].name = "VaaToCao";
    tradeDescriptionList[27].name = "CaoToVaa";
    tradeDescriptionList[28].name = "BauToCao";
    tradeDescriptionList[29].name = "CaoToBau";
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::downloadClicked() {
    ui->textBrowser->clear();
    for(int i = 0; i < 30; i++) {
        tradeDescriptionList[i].websiteParser->getWebsite(tradeDescriptionList[i].link);
    }
}


void MainWindow::parseWebsiteSource(QNetworkReply* reply, int wpID) {
    QString strReply = reply->readAll();
    if(strReply.size() == 0) {
        std::cout << "Konnte keine Daten von der Website empfangen!" << std::endl;
        return;
    }
    QList<buyAndSellVal> val = WebsiteParser::getBuyAndSellVal(strReply);
    tradeDescriptionList[wpID].label->setText(formatRatiosForLabel(val));
    CurrencyDatabase::writeToDB(&val, QString(tradeDescriptionList[wpID].name + ".csv"));
}


void MainWindow::writeToTextBrowser(const QString output) {
    ui->textBrowser->append(output);
}


QString MainWindow::formatRatiosForLabel(QList<buyAndSellVal> val, int view) {
    if(view == 1) {                                                                                                 //-> 9.00/8.50/8.33
        return QString::number(val.at(0).youSell/val.at(0).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(1).youSell/val.at(1).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(2).youSell/val.at(2).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(3).youSell/val.at(3).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(4).youSell/val.at(4).youBuy, 'f', 2);
    } else if(view == 2) {                                                                                          //-> 100:10/180:20/17:2
        return QString::number(val.at(0).youSell, 'f', 2) + ":" + QString::number(val.at(0).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(1).youSell, 'f', 2) + ":" + QString::number(val.at(1).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(2).youSell, 'f', 2) + ":" + QString::number(val.at(2).youBuy, 'f', 2);
    } else if(view == 3) {                                                                                          //-> 10:1/9:1/8.5:1
        return QString::number(val.at(0).youSell/val.at(0).youBuy, 'f', 2) + ":1" +
                                        "/" + QString::number(val.at(1).youSell/val.at(1).youBuy, 'f', 2) + ":1" +
                                        "/" + QString::number(val.at(2).youSell/val.at(2).youBuy, 'f', 2) + ":1";
    } else if(view == 4) {                                                                                          // 1 inverted
        return QString::number(val.at(0).youSell/val.at(0).youBuy, 'f', 2) +
                                        "/" + QString::number(val.at(1).youBuy/val.at(1).youSell, 'f', 2) +
                                        "/" + QString::number(val.at(2).youBuy/val.at(2).youSell, 'f', 2) +
                                        "/" + QString::number(val.at(3).youBuy/val.at(3).youSell, 'f', 2) +
                                        "/" + QString::number(val.at(4).youBuy/val.at(4).youSell, 'f', 2);
    } else if(view == 5) {                                                                                          // 2 inverted
        return QString::number(val.at(0).youBuy, 'f', 2) + ":" + QString::number(val.at(0).youSell, 'f', 2) +
                                        "/" + QString::number(val.at(1).youBuy, 'f', 2) + ":" + QString::number(val.at(1).youSell, 'f', 2) +
                                        "/" + QString::number(val.at(2).youBuy, 'f', 2) + ":" + QString::number(val.at(2).youSell, 'f', 2);
    } else if(view == 6) {                                                                                          // 3 inverted
        return QString::number(val.at(0).youBuy/val.at(0).youSell, 'f', 2) + ":1" +
                                        "/" + QString::number(val.at(1).youBuy/val.at(1).youSell, 'f', 2) + ":1" +
                                        "/" + QString::number(val.at(2).youBuy/val.at(2).youSell, 'f', 2) + ":1";
    } else {
        return "";
    }
}


void MainWindow::pushButtonAltClicked() {
    std::cout << "pushButtonAltClicked()" << std::endl;
    if(ui->checkBoxAltToCao->isChecked() || ui->checkBoxCaoToAlt->isChecked()) {
        ui->checkBoxAltToCao->setChecked(false);
        ui->checkBoxCaoToAlt->setChecked(false);
    } else {
        ui->checkBoxAltToCao->setChecked(true);
        ui->checkBoxCaoToAlt->setChecked(true);
    }

}


void MainWindow::pushButtonFusClicked() {
    std::cout << "pushButtonFusClicked()" << std::endl;
    if(ui->checkBoxFusToCao->isChecked() || ui->checkBoxCaoToFus->isChecked()) {
        ui->checkBoxFusToCao->setChecked(false);
        ui->checkBoxCaoToFus->setChecked(false);
    } else {
        ui->checkBoxFusToCao->setChecked(true);
        ui->checkBoxCaoToFus->setChecked(true);
    }

}


void MainWindow::pushButtonExaClicked() {
    std::cout << "pushButtonExaClicked()" << std::endl;
    if(ui->checkBoxExaToCao->isChecked() || ui->checkBoxCaoToExa->isChecked()) {
        ui->checkBoxExaToCao->setChecked(false);
        ui->checkBoxCaoToExa->setChecked(false);
    } else {
        ui->checkBoxExaToCao->setChecked(true);
        ui->checkBoxCaoToExa->setChecked(true);
    }

}


void MainWindow::pushButtonAlcClicked() {
    std::cout << "pushButtonAlcClicked()" << std::endl;
    if(ui->checkBoxAlcToCao->isChecked() || ui->checkBoxCaoToAlc->isChecked()) {
        ui->checkBoxAlcToCao->setChecked(false);
        ui->checkBoxCaoToAlc->setChecked(false);
    } else {
        ui->checkBoxAlcToCao->setChecked(true);
        ui->checkBoxCaoToAlc->setChecked(true);
    }

}


void MainWindow::pushButtonGCPClicked() {
    std::cout << "pushButtonGCPClicked()" << std::endl;
    if(ui->checkBoxGCPToCao->isChecked() || ui->checkBoxCaoToGCP->isChecked()) {
        ui->checkBoxGCPToCao->setChecked(false);
        ui->checkBoxCaoToGCP->setChecked(false);
    } else {
        ui->checkBoxGCPToCao->setChecked(true);
        ui->checkBoxCaoToGCP->setChecked(true);
    }

}


void MainWindow::pushButtonChrClicked() {
    std::cout << "pushButtonChrClicked()" << std::endl;
    if(ui->checkBoxChrToCao->isChecked() || ui->checkBoxCaoToChr->isChecked()) {
        ui->checkBoxChrToCao->setChecked(false);
        ui->checkBoxCaoToChr->setChecked(false);
    } else {
        ui->checkBoxChrToCao->setChecked(true);
        ui->checkBoxCaoToChr->setChecked(true);
    }

}


void MainWindow::pushButtonJewClicked() {
    std::cout << "pushButtonJewClicked()" << std::endl;
    if(ui->checkBoxJewToCao->isChecked() || ui->checkBoxCaoToJew->isChecked()) {
        ui->checkBoxJewToCao->setChecked(false);
        ui->checkBoxCaoToJew->setChecked(false);
    } else {
        ui->checkBoxJewToCao->setChecked(true);
        ui->checkBoxCaoToJew->setChecked(true);
    }

}


void MainWindow::pushButtonChaClicked() {
    std::cout << "pushButtonChaClicked()" << std::endl;
    if(ui->checkBoxChaToCao->isChecked() || ui->checkBoxCaoToCha->isChecked()) {
        ui->checkBoxChaToCao->setChecked(false);
        ui->checkBoxCaoToCha->setChecked(false);
    } else {
        ui->checkBoxChaToCao->setChecked(true);
        ui->checkBoxCaoToCha->setChecked(true);
    }

}


void MainWindow::pushButtonChiClicked() {
    std::cout << "pushButtonChiClicked()" << std::endl;
    if(ui->checkBoxChiToCao->isChecked() || ui->checkBoxCaoToChi->isChecked()) {
        ui->checkBoxChiToCao->setChecked(false);
        ui->checkBoxCaoToChi->setChecked(false);
    } else {
        ui->checkBoxChiToCao->setChecked(true);
        ui->checkBoxCaoToChi->setChecked(true);
    }

}


void MainWindow::pushButtonScoClicked() {
    std::cout << "pushButtonScoClicked()" << std::endl;
    if(ui->checkBoxScoToCao->isChecked() || ui->checkBoxCaoToSco->isChecked()) {
        ui->checkBoxScoToCao->setChecked(false);
        ui->checkBoxCaoToSco->setChecked(false);
    } else {
        ui->checkBoxScoToCao->setChecked(true);
        ui->checkBoxCaoToSco->setChecked(true);
    }

}


void MainWindow::pushButtonBleClicked() {
    std::cout << "pushButtonBleClicked()" << std::endl;
    if(ui->checkBoxBleToCao->isChecked() || ui->checkBoxCaoToBle->isChecked()) {
        ui->checkBoxBleToCao->setChecked(false);
        ui->checkBoxCaoToBle->setChecked(false);
    } else {
        ui->checkBoxBleToCao->setChecked(true);
        ui->checkBoxCaoToBle->setChecked(true);
    }

}


void MainWindow::pushButtonRegClicked() {
    std::cout << "pushButtonRegClicked()" << std::endl;
    if(ui->checkBoxRegToCao->isChecked() || ui->checkBoxCaoToReg->isChecked()) {
        ui->checkBoxRegToCao->setChecked(false);
        ui->checkBoxCaoToReg->setChecked(false);
    } else {
        ui->checkBoxRegToCao->setChecked(true);
        ui->checkBoxCaoToReg->setChecked(true);
    }

}


void MainWindow::pushButtonDivClicked() {
    std::cout << "pushButtonDivClicked()" << std::endl;
    if(ui->checkBoxDivToCao->isChecked() || ui->checkBoxCaoToDiv->isChecked()) {
        ui->checkBoxDivToCao->setChecked(false);
        ui->checkBoxCaoToDiv->setChecked(false);
    } else {
        ui->checkBoxDivToCao->setChecked(true);
        ui->checkBoxCaoToDiv->setChecked(true);
    }

}


void MainWindow::pushButtonVaaClicked() {
    std::cout << "pushButtonVaaClicked()" << std::endl;
    if(ui->checkBoxVaaToCao->isChecked() || ui->checkBoxCaoToVaa->isChecked()) {
        ui->checkBoxVaaToCao->setChecked(false);
        ui->checkBoxCaoToVaa->setChecked(false);
    } else {
        ui->checkBoxVaaToCao->setChecked(true);
        ui->checkBoxCaoToVaa->setChecked(true);
    }

}


void MainWindow::pushButtonBauClicked() {
    std::cout << "pushButtonBauClicked()" << std::endl;
    if(ui->checkBoxBauToCao->isChecked() || ui->checkBoxCaoToBau->isChecked()) {
        ui->checkBoxBauToCao->setChecked(false);
        ui->checkBoxCaoToBau->setChecked(false);
    } else {
        ui->checkBoxBauToCao->setChecked(true);
        ui->checkBoxCaoToBau->setChecked(true);
    }

}


