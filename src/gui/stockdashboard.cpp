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

  stockGraph = new StockGraph(stocks[1], this);

  ui->verticalLayout_2->addWidget(stockGraph);
  ui->symbol->setText(QString((stocks[1]->getSymbol()).c_str()));
}

StockDashboard::~StockDashboard() {
  delete ui;
  delete stockGraph;
}
