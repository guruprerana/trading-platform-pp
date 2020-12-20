#include "stockdashboard.h"
#include "ui_stockdashboard.h"

StockDashboard::StockDashboard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockDashboard) {
  ui->setupUi(this);

  stocks.append(new Stock("AAPL")); // Apple
  stocks.append(new Stock("MSFT")); // Microsoft
  stocks.append(new Stock("AMZN")); // Amazon
  stocks.append(new Stock("FB")); // Facebook

  stockGraphThreeDays = new StockGraphThreeDays(stocks[1], this);
  stockGraphSixMonths = new StockGraphSixMonths(stocks[1], this);
  stockGraphOneMonth = new StockGraphOneMonth(stocks[1], this);

  ui->threeDays->layout()->addWidget(stockGraphThreeDays);
  ui->oneMonth->layout()->addWidget(stockGraphOneMonth);
  ui->sixMonths->layout()->addWidget(stockGraphSixMonths);
  ui->symbol->setText(QString((stocks[1]->getSymbol()).c_str()));
}

StockDashboard::~StockDashboard() {
  delete ui;
  delete stockGraphThreeDays;
  delete stockGraphOneMonth;
  delete stockGraphSixMonths;
}
