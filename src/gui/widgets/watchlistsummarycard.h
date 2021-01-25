#ifndef WATCHLISTSUMMARYCARD_H
#define WATCHLISTSUMMARYCARD_H

#include <QWidget>
#include "../../components/stock.h"

namespace Ui {
class WatchlistSummaryCard;
}

class WatchlistSummaryCard : public QWidget {
  Q_OBJECT

 public:
  explicit WatchlistSummaryCard(Stock *stock, QWidget *parent = nullptr);
  ~WatchlistSummaryCard();

 private:
  Ui::WatchlistSummaryCard *ui;
  Stock *stock;
};

#endif // WATCHLISTSUMMARYCARD_H
