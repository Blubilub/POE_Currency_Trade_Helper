#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFile>
#include <QIODevice>
#include "currencydatabase.h"


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

    linkList[0]  = "http://currency.poe.trade/search?league=Standard&online=x&want=1&have=4";  //alt->c  x
    linkList[1]  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=1";  //c->alt  c
    linkList[2]  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=2";  //fus->c  x
    linkList[3]  = "http://currency.poe.trade/search?league=Standard&online=x&want=2&have=4";  //c->fus  c
    linkList[4]  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=6";  //exa->c  x
    linkList[5]  = "http://currency.poe.trade/search?league=Standard&online=x&want=6&have=4";  //c->exa  c
    linkList[6]  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=3";  //alc->c  x
    linkList[7]  = "http://currency.poe.trade/search?league=Standard&online=x&want=3&have=4";  //c->alc  c
    linkList[8]  = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=5";  //gcp->c  x
    linkList[9]  = "http://currency.poe.trade/search?league=Standard&online=x&want=5&have=4";  //c->gcp  c
    linkList[10] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=7";  //chr->c  x
    linkList[11] = "http://currency.poe.trade/search?league=Standard&online=x&want=7&have=4";  //c->chr  c
    linkList[12] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=8";  //jew->c  x
    linkList[13] = "http://currency.poe.trade/search?league=Standard&online=x&want=8&have=4";  //c->jew  c
    linkList[14] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=9";  //cha->c  x
    linkList[15] = "http://currency.poe.trade/search?league=Standard&online=x&want=9&have=4";  //c->cha  c
    linkList[16] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=10"; //chi->c  x
    linkList[17] = "http://currency.poe.trade/search?league=Standard&online=x&want=10&have=4"; //c->chi  c
    linkList[18] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=11"; //sco->c  x
    linkList[19] = "http://currency.poe.trade/search?league=Standard&online=x&want=11&have=4"; //c->sco  c
    linkList[20] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=12"; //ble->c  x
    linkList[21] = "http://currency.poe.trade/search?league=Standard&online=x&want=12&have=4"; //c->ble  c
    linkList[22] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=13"; //reg->c  x
    linkList[23] = "http://currency.poe.trade/search?league=Standard&online=x&want=13&have=4"; //c->reg  c
    linkList[24] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=15"; //div->c  x
    linkList[25] = "http://currency.poe.trade/search?league=Standard&online=x&want=15&have=4"; //c->div  c
    linkList[26] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=16"; //vaa->c  x
    linkList[27] = "http://currency.poe.trade/search?league=Standard&online=x&want=16&have=4"; //c->vaa  c
    linkList[28] = "http://currency.poe.trade/search?league=Standard&online=x&want=4&have=21"; //bau->c  x
    linkList[29] = "http://currency.poe.trade/search?league=Standard&online=x&want=21&have=4"; //c->bau  c

    for(int i = 0; i < 30; i++) {
        wp[i] = new WebsiteParser(i);
        connect(wp[i], SIGNAL(finishedDownloading(QNetworkReply*, int)), this, SLOT(parseWebsiteSource(QNetworkReply*, int)));
    }


}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::downloadClicked() {
    ui->textBrowser->clear();
    for(int i = 0; i < 30; i++) {
        wp[i]->getWebsite(linkList[i]);
    }
}


void MainWindow::parseWebsiteSource(QNetworkReply* reply, int wpID) {
    QString strReply = reply->readAll();
    QList<buyAndSellVal> val = WebsiteParser::getBuyAndSellVal(strReply);

//*************************************************************************************
//***********                 QFile Example                                ************
//*************************************************************************************
/*
    QFile database("testDB.csv");
    database.setFileName("database/" + database.fileName());

    QString errMsg;
    QFileDevice::FileError err = QFileDevice::NoError;
    if(!database.exists()) {
        if (!database.open(QIODevice::WriteOnly)) {
            errMsg = database.errorString();
            err = database.error();
            ui->textBrowser->append(errMsg);
            return;
        }
        database.close();
    }

    if (!database.open(QIODevice::ReadOnly)) {
        errMsg = database.errorString();
        err = database.error();
        ui->textBrowser->append(errMsg);
        return;
    }
    QTextStream in(&database);
    QString f = in.readLine();
    database.close();

    if (!database.open(QIODevice::WriteOnly | QIODevice::Append)) {
        errMsg = database.errorString();
        err = database.error();
        ui->textBrowser->append(errMsg);
        return;
    }
    QString dbData = "Textfeld 1,Textfeld 2,Textfeld 3,Textfeld 4,Textfeld 5,Textfeld 6\n3423,2542,6553,52344,5435,534256\n";
    QTextStream out(&database);
    out << dbData;
    database.close();
*/
//*************************************************************************************
    QFile database("");


    std::cout << wpID << std::endl;
    QString dbData;
    switch(wpID) {
    case 0:
        ui->labelAltToCao->setText(formatRatiosForLabel(val));
        database.setFileName("AltToCao.csv");
        break;
    case 1:
        ui->labelCaoToAlt->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToAlt.csv");
        break;
    case 2:
        ui->labelFusToCao->setText(formatRatiosForLabel(val));
        database.setFileName("FusToCao.csv");
        break;
    case 3:
        ui->labelCaoToFus->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToFus.csv");
        break;
    case 4:
        ui->labelExaToCao->setText(formatRatiosForLabel(val));
        database.setFileName("ExaToCao.csv");
        break;
    case 5:
        ui->labelCaoToExa->setText(formatRatiosForLabel(val, 6));
        database.setFileName("CaoToExa.csv");
        break;
    case 6:
        ui->labelAlcToCao->setText(formatRatiosForLabel(val));
        database.setFileName("AlcToCao.csv");
        break;
    case 7:
        ui->labelCaoToAlc->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToAlc.csv");
        break;
    case 8:
        ui->labelGCPToCao->setText(formatRatiosForLabel(val));
        database.setFileName("GCPToCao.csv");
        break;
    case 9:
        ui->labelCaoToGCP->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToGCP.csv");
        break;
    case 10:
        ui->labelChrToCao->setText(formatRatiosForLabel(val));
        database.setFileName("ChrToCao.csv");
        break;
    case 11:
        ui->labelCaoToChr->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToChr.csv");
        break;
    case 12:
        ui->labelJewToCao->setText(formatRatiosForLabel(val));
        database.setFileName("JewToCao.csv");
        break;
    case 13:
        ui->labelCaoToJew->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToJew.csv");
        break;
    case 14:
        ui->labelChaToCao->setText(formatRatiosForLabel(val));
        database.setFileName("ChaToCao.csv");
        break;
    case 15:
        ui->labelCaoToCha->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToCha.csv");
        break;
    case 16:
        ui->labelChiToCao->setText(formatRatiosForLabel(val));
        database.setFileName("ChiToCao.csv");
        break;
    case 17:
        ui->labelCaoToChi->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToChi.csv");
        break;
    case 18:
        ui->labelScoToCao->setText(formatRatiosForLabel(val));
        database.setFileName("ScoToCao.csv");
        break;
    case 19:
        ui->labelCaoToSco->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToSco.csv");
        break;
    case 20:
        ui->labelBleToCao->setText(formatRatiosForLabel(val));
        database.setFileName("BleToCao.csv");
        break;
    case 21:
        ui->labelCaoToBle->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToBle.csv");
        break;
    case 22:
        ui->labelRegToCao->setText(formatRatiosForLabel(val));
        database.setFileName("RegToCao.csv");
        break;
    case 23:
        ui->labelCaoToReg->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToReg.csv");
        break;
    case 24:
        ui->labelDivToCao->setText(formatRatiosForLabel(val));
        database.setFileName("DivToCao.csv");
        break;
    case 25:
        ui->labelCaoToDiv->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToDiv.csv");
        break;
    case 26:
        ui->labelVaaToCao->setText(formatRatiosForLabel(val));
        database.setFileName("VaaToCao.csv");
        break;
    case 27:
        ui->labelCaoToVaa->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToVaa.csv");
        break;
    case 28:
       // ui->labelBauToCao->setText(formatRatiosForLabel(val));
        database.setFileName("BauToCao.csv");
        break;
    case 29:
        //ui->labelCaoToBau->setText(formatRatiosForLabel(val));
        database.setFileName("CaoToBau.csv");
        break;
    default:
        break;

    }

    database.setFileName("database/" + database.fileName());
    QString errMsg;
    QFileDevice::FileError err = QFileDevice::NoError;

    if(!database.exists()) {
        if (!database.open(QIODevice::ReadWrite | QIODevice::Append)) {
            errMsg = database.errorString();
            err = database.error();
            ui->textBrowser->append(errMsg);
        }
        {
            QTextStream out(&database);
            out << "date,youSell,youBuy\n";
        }
    } else {
        if (!database.open(QIODevice::ReadWrite | QIODevice::Append)) {
            errMsg = database.errorString();
            err = database.error();
            ui->textBrowser->append(errMsg);
        }
    }
    dbData = CurrencyDatabase::formatDataForDB(&val.at(0));

    for(int i = 5; i<5 && i<val.size(); i++){
        QTextStream out(&database);
        out << dbData;
    }
    database.close();
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


