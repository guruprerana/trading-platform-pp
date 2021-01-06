#ifndef STRATEGYGRAPH_H
#define STRATEGYGRAPH_H

#include "stockgraph.h"
#include "components/stock.h"

class StrategyGraph : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StrategyGraph(QWidget *parent = nullptr);
  ~StrategyGraph();
  void setStock(Stock *other_stock);
  void updateData(bool firstTime);
  void initTimeRange();
  void setCandlestickBinSize();

 private slots:
  void realtimeDataSlot();
};

#endif // STRATEGYGRAPH_H
