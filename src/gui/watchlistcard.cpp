#include "watchlistcard.h"
#include "ui_watchlistcard.h"

WatchlistCard::WatchlistCard(Stock *stock, QWidget *parent) :
  QWidget(parent),
  stock(stock),
  ui(new Ui::WatchlistCard) {
  ui->setupUi(this);

  ui->symbol->setText(QString(stock->getSymbol().c_str()));
}

WatchlistCard::~WatchlistCard() {
  delete ui;
  delete stock;
}
