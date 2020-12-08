#ifndef STOCKDASHBOARD_H
#define STOCKDASHBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include "stockgraph.h"

namespace Ui {
class StockDashboard;
}

class StockDashboard : public QWidget {
  Q_OBJECT

 public:
  explicit StockDashboard(QWidget *parent = nullptr);
  ~StockDashboard();

 private:
  Ui::StockDashboard *ui;

  StockGraph *stockGraph;
};

#endif // STOCKDASHBOARD_H
