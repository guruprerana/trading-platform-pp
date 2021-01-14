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
  void drawEMA(const QVector<double> &timestamp_ema6,
               const QVector<double> &price_ema6,
               const QVector<double> &timestamp_ema11,
               const QVector<double> &price_ema11);
  void drawLR(double slope, double intercept, const QVector<double> &timestamp);
  void addGraph(QCPGraph *graph);
  void removeAllGraphs();

 private slots:
  void realtimeDataSlot();

 private:
  QCPGraph *sma20;
  QCPGraph *sma50;
  QCPGraph *ema6;
  QCPGraph *ema11;
  QCPGraph *lr;
};

#endif // STRATEGYGRAPH_H
