#include "watchlistcard.h"
#include "ui_watchlistcard.h"

#include <QDebug>

WatchlistCard::WatchlistCard(Stock *stock, QWidget *parent) :
  QWidget(parent),
  stock(stock),
  ui(new Ui::WatchlistCard) {
  ui->setupUi(this);

  ui->symbol->setText(QString(stock->getSymbol().c_str()));
  connect(ui->symbol, SIGNAL(clicked()), this, SIGNAL(clicked()));
}

WatchlistCard::~WatchlistCard() {
  delete ui;
  delete stock;
}

void WatchlistCard::setChecked(bool isChecked) {
  ui->symbol->setChecked(isChecked);
}
