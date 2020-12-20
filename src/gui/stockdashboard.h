#ifndef STOCKDASHBOARD_H
#define STOCKDASHBOARD_H

#include <QWidget>
#include "stockgraphthreedays.h"
#include "stockgraphonemonth.h"
#include "stockgraphsixmonths.h"
#include "components/stock.h"

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
  QVector<Stock *> stocks;
  StockGraphThreeDays *stockGraphThreeDays;
  StockGraphOneMonth *stockGraphOneMonth;
  StockGraphSixMonths *stockGraphSixMonths;
};

#endif // STOCKDASHBOARD_H
