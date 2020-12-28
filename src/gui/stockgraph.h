#ifndef STOCKGRAPH_H
#define STOCKGRAPH_H

#include <QTimer>
#include <QWidget>
#include "components/stock.h"
#include <QVariant>
#include "library/qcustomplot.h"
namespace Ui {
class StockGraph;
}

class StockGraph : public QWidget {
  Q_OBJECT

 public:
  explicit StockGraph(Stock *stock, QWidget *parent = nullptr);
  ~StockGraph();
  void clearData();
  void plot();
  void initLineChart();
  void initCandleStick();
  virtual void initTimeRange() = 0;
  virtual void setCandlestickBinSize() = 0;

 protected slots:
  virtual void realtimeDataSlot() = 0;
  void mouse_press(QMouseEvent *event);
 protected:
  Stock *stock;
  Ui::StockGraph *ui;
  QCPGraph *lineChart;
  QCPFinancial *candleStick;
  QVector<double> timestamp, open, high, low, close;
  QTimer dataTimer;
  QCPItemTracer *tracer;
  QCPItemText *textLabel;
};
QVector<double> convert_to_vector(QJsonObject, std::string);

#define StockGraph_iid "com.acme.StockGraph"

Q_DECLARE_INTERFACE(StockGraph, StockGraph_iid)

#endif // STOCKGRAPH_H
