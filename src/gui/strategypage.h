#ifndef STRATEGYPAGE_H
#define STRATEGYPAGE_H

#include <QWidget>
#include "components/stock.h"
#include "watchlistcard.h"
#include "strategygraph.h"
#include "recommendation/strategy.h"

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
  void simulateStrategy();

 private slots:
  void on_comboBox_currentIndexChanged(int index);

 private:
  Ui::StrategyPage *ui;
  int currentStockId;
  Strategy *strategy;
  StrategyGraph *strategyGraph;
  QVector<Stock *> watchlistStocks;
  QVector<WatchlistCard *> watchlistCards;
};

#endif // STRATEGYPAGE_H
