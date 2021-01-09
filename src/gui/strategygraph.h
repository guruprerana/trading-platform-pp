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
  void drawSMA(const QVector<double> &timestamp_sma20,
               const QVector<double> &price_sma20,
               const QVector<double> &timestamp_sma50,
               const QVector<double> &price_sma50);

 private slots:
  void realtimeDataSlot();

 private:
  QCPGraph *sma20;
  QCPGraph *sma50;
};

#endif // STRATEGYGRAPH_H
