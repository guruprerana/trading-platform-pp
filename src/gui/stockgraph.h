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
  explicit StockGraph(QWidget *parent = nullptr);
  ~StockGraph();
  void clearData();
  void plot();

 private slots:
  void realtimeDataSlot();

 private:
  Ui::StockGraph *ui;
  QVector<double> timestamp, high;
  QTimer dataTimer;
  Stock *stock;
};
QVector<double> convert_to_vector(QJsonObject, std::string);

#endif // STOCKGRAPH_H
