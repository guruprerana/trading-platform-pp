#ifndef WATCHLISTCARD_H
#define WATCHLISTCARD_H

#include <QWidget>
#include "components/stock.h"

namespace Ui {
class WatchlistCard;
}

class WatchlistCard : public QWidget {
  Q_OBJECT

 public:
  explicit WatchlistCard(Stock *stock, QWidget *parent = nullptr);
  ~WatchlistCard();

  void setChecked(bool isChecked);

 signals:
  void clicked();

 private:
  Ui::WatchlistCard *ui;
  Stock *stock;
};

#endif // WATCHLISTCARD_H
