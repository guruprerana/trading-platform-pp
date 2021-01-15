#include "watchlistsummarycard.h"
#include "ui_watchlistsummarycard.h"

WatchlistSummaryCard::WatchlistSummaryCard(Stock *stock, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WatchlistSummaryCard) {
  ui->setupUi(this);

  this->stock = stock;

  stock->getDataByDay();

  std::string ticker = stock->getSymbol();
  stock->updateDataByMinute();
  stock->updateDataByDay();
  QMap<std::string, QVector<double>> valuation = stock->getDataByMinute();
  double today = stock->getDataByDay()["c"].toArray().last().toDouble();
  double yesterday = stock->getDataByDay()["c"].toArray().at(stock->getDataByDay()["c"].toArray().size()-2).toDouble();
  double delta = 100 * (today - yesterday) / yesterday;

  ui->valuation->setText("Valuation: $" + QString::number(valuation["c"].last(), 'g', 3));
  ui->ticker->setText(QString::fromStdString(ticker));
  ui->delta->setText("Daily Change: " + QString::number(delta, 'g', 3) + "%");

}

WatchlistSummaryCard::~WatchlistSummaryCard() {
  delete ui;
}
