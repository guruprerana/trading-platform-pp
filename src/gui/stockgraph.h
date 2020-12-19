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

 private slots:
  void realtimeDataSlot();

 private:
  Stock *stock;
  Ui::StockGraph *ui;
  QCPGraph *lineChart;
  QCPFinancial *candleStick;
  QVector<double> timestamp, open, high, low, close;
  QTimer dataTimer;
};
QVector<double> convert_to_vector(QJsonObject, std::string);

#endif // STOCKGRAPH_H
