#ifndef STOCKGRAPHTHREEDAYS_H
#define STOCKGRAPHTHREEDAYS_H

#include "stockgraph.h"
#include "components/stock.h"

class StockGraphThreeDays : public StockGraph {
  Q_INTERFACES(StockGraph)

 public:
  explicit StockGraphThreeDays(Stock *stock, QWidget *parent = nullptr);
  ~StockGraphThreeDays();
  void initTimeRange();

 private slots:
  void realtimeDataSlot();
};

#endif // STOCKGRAPHTHREEDAYS_H
