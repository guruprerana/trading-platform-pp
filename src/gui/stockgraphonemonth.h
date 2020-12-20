#ifndef STOCKGRAPHONEMONTH_H
#define STOCKGRAPHONEMONTH_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphOneMonth : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphOneMonth(Stock *stock, QWidget *parent = nullptr);
  ~StockGraphOneMonth();
  void initTimeRange();

 private slots:
  void realtimeDataSlot();
};

#endif // STOCKGRAPHONEMONTH_H
