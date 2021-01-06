#ifndef STOCKGRAPHTHREEDAYS_H
#define STOCKGRAPHTHREEDAYS_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphThreeDays : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphThreeDays(QWidget *parent = nullptr);
  ~StockGraphThreeDays();
  void setStock(Stock *other_stock);
  void updateData(bool firstTime);
  void initTimeRange();
  void setCandlestickBinSize();

 private slots:
  void realtimeDataSlot();
};

#endif // STOCKGRAPHTHREEDAYS_H
