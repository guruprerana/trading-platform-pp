#include "watchlistsummarycard.h"
#include "ui_watchlistsummarycard.h"

WatchlistSummaryCard::WatchlistSummaryCard(Stock *stock, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WatchlistSummaryCard) {
  ui->setupUi(this);

  this->stock = stock;
}

WatchlistSummaryCard::~WatchlistSummaryCard() {
  delete ui;
}
