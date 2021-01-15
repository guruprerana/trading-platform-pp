#ifndef STOCKGRAPHONEMONTH_H
#define STOCKGRAPHONEMONTH_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphOneMonth : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphOneMonth(QWidget *parent = nullptr);
  ~StockGraphOneMonth();
  void setStock(Stock *other_stock);
  void updateData(bool firstTime);
  void initTimeRange();
  void setCandlestickBinSize();

 private slots:
  void realtimeDataSlot();
};

#endif // STOCKGRAPHONEMONTH_H
