#include "watchlistsummarycard.h"
#include "ui_watchlistsummarycard.h"

WatchlistSummaryCard::WatchlistSummaryCard(Stock *stock, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WatchlistSummaryCard) {
  ui->setupUi(this);

  this->stock = stock;

  stock->getDataByDay();

  std::string ticker = stock->getSymbol();
  QMap<std::string, QVector<double>> valuation = stock->getDataByMinute();
  double delta = 100 * (stock->getDataByDay()["c"].toArray().last().toDouble()) / stock->getDataByDay()["c"].toArray().last().toDouble();

  ui->valuation->setText(QString::number(valuation["c"].last()));
  ui->ticker->setText(QString::fromStdString(ticker));
  ui->delta->setText(QString::number(delta));

}

WatchlistSummaryCard::~WatchlistSummaryCard() {
  delete ui;
}
