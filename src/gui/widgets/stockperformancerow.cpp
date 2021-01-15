#include "stockperformancerow.h"
#include "ui_stockperformancerow.h"

StockPerformanceRow::StockPerformanceRow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockPerformanceRow) {
  ui->setupUi(this);
}

StockPerformanceRow::~StockPerformanceRow() {
  delete ui;
}

void StockPerformanceRow::from(Portfolio *portfolio, qint32 id,
                               QString symbol) {
  ui->nLabel->setText(QString::number(id));
  ui->equityLabel->setText(symbol);
  ui->quantityLabel->setText(QString::number(portfolio->getOwnedQuantity(symbol),
                             'f', 4));
  ui->marketValueLabel->setText(QString::number(portfolio->getMarketValue(
                                  symbol), 'f', 4) + "$");
  // ui->dayChangeLabel
  ui->costBasisLabel->setText(QString::number(portfolio->getCostBasis(symbol),
                              'f', 4) + "$");
  ui->gainLossLabel->setText(QString::number(portfolio->getTotalGainLoss(
                               symbol), 'f', 4) + "$");
  ui->percentAccountLabel->setText(QString::number(portfolio->getPercentOfAccount(
                                     symbol), 'f', 4) + "%");
}
