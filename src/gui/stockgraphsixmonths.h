#ifndef STOCKGRAPHSIXMONTHS_H
#define STOCKGRAPHSIXMONTHS_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphSixMonths : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphSixMonths(Stock *stock, QWidget *parent = nullptr);
  ~StockGraphSixMonths();
  void initTimeRange();
  void setCandlestickBinSize();

 private slots:
  void realtimeDataSlot();
};

#endif // STOCKGRAPHSIXMONTHS_H
