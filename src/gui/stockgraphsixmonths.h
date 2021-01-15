#ifndef STOCKGRAPHSIXMONTHS_H
#define STOCKGRAPHSIXMONTHS_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphSixMonths : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphSixMonths(QWidget *parent = nullptr);
  ~StockGraphSixMonths();
  void setStock(Stock *other_stock);
  void updateData(bool firstTime);
  void initTimeRange();
  void setCandlestickBinSize();

 private slots:
  void realtimeDataSlot();
};

#endif // STOCKGRAPHSIXMONTHS_H
