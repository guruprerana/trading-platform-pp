#ifndef STRATEGYPAGE_H
#define STRATEGYPAGE_H

#include <QWidget>
#include "components/stock.h"
#include "watchlistcard.h"
#include "strategygraph.h"

namespace Ui {
class StrategyPage;
}

class StrategyPage : public QWidget {
  Q_OBJECT

 public:
  explicit StrategyPage(QWidget *parent = nullptr);
  ~StrategyPage();

  void updateWatchlistStocks(QVector<Stock *> other_watchlistStocks);
  void changeCurrentStock(int stockId);

 private:
  Ui::StrategyPage *ui;
  int currentStockId;
  StrategyGraph *strategyGraph;
  QVector<Stock *> watchlistStocks;
  QVector<WatchlistCard *> watchlistCards;
};

#endif // STRATEGYPAGE_H
