#include "stockdashboard.h"
#include "ui_stockdashboard.h"
#include "companynewscard.h"
#include "helper/helper.h"

StockDashboard::StockDashboard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockDashboard) {
  ui->setupUi(this);

  newsId = 0;
  stocks.append(new Stock("AAPL")); // Apple
  stocks.append(new Stock("MSFT")); // Microsoft
  stocks.append(new Stock("AMZN")); // Amazon
  stocks.append(new Stock("FB")); // Facebook

  stockGraphOneDay = new StockGraphOneDay(stocks[0], this);
  stockGraphThreeDays = new StockGraphThreeDays(stocks[0], this);
  stockGraphSixMonths = new StockGraphSixMonths(stocks[0], this);
  stockGraphOneMonth = new StockGraphOneMonth(stocks[0], this);

  stocks[0]->updateNews();
  QJsonArray companyNews = stocks[0]->getNews();

  for (auto v : companyNews) {
    QJsonObject json = v.toObject();
    long unixTimestamp = json["datetime"].toVariant().toInt();
    std::string readableTime = helper::convertToFullTimeReadable(unixTimestamp);

    CompanyNewsCard *companyNewsCard = new CompanyNewsCard(
      json["headline"].toString(),
      json["url"].toString(),
      QString(readableTime.c_str()),
      json["summary"].toString(),
      ui->stackedWidget);
    ui->stackedWidget->addWidget(companyNewsCard);
  }

  ui->oneDay->layout()->addWidget(stockGraphOneDay);
  ui->threeDays->layout()->addWidget(stockGraphThreeDays);
  ui->oneMonth->layout()->addWidget(stockGraphOneMonth);
  ui->sixMonths->layout()->addWidget(stockGraphSixMonths);
  ui->symbol->setText(QString((stocks[0]->getSymbol()).c_str()));
}

StockDashboard::~StockDashboard() {
  delete ui;
  delete stockGraphThreeDays;
  delete stockGraphOneMonth;
  delete stockGraphSixMonths;
}

void StockDashboard::on_leftButton_clicked() {
  if (ui->stackedWidget->count() == 0 || newsId == 0) {
    return;
  }

  newsId = (newsId + ui->stackedWidget->count() - 1) % ui->stackedWidget->count();
  ui->stackedWidget->setCurrentIndex(newsId);
}

void StockDashboard::on_rightButton_clicked() {
  if (ui->stackedWidget->count() == 0 ||
      newsId == ui->stackedWidget->count() - 1) {
    return;
  }

  newsId = (newsId + 1) % ui->stackedWidget->count();
  ui->stackedWidget->setCurrentIndex(newsId);
}
