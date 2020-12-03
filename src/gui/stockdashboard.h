#ifndef STOCKDASHBOARD_H
#define STOCKDASHBOARD_H

#include <QWidget>
#include <QHBoxLayout>
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
  QHBoxLayout *layout;
};

#endif // STOCKDASHBOARD_H
