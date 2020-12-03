#ifndef STOCKGRAPH_H
#define STOCKGRAPH_H

#include <QWidget>

namespace Ui {
class StockGraph;
}

class StockGraph : public QWidget {
  Q_OBJECT

 public:
  explicit StockGraph(QWidget *parent = nullptr);
  ~StockGraph();

 private:
  Ui::StockGraph *ui;
};

#endif // STOCKGRAPH_H
