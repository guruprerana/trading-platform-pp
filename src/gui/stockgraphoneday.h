#ifndef STOCKGRAPHONEDAY_H
#define STOCKGRAPHONEDAY_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphOneDay : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphOneDay(QWidget *parent = nullptr);
  ~StockGraphOneDay();
  void setStock(Stock *other_stock);
  void updateData();
  void initTimeRange();
  void setCandlestickBinSize();

 private slots:
  void realtimeDataSlot();
};


#endif // STOCKGRAPHONEDAY_H
