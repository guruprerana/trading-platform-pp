#ifndef STOCKDASHBOARD_H
#define STOCKDASHBOARD_H

#include <QWidget>
#include "stockgraphoneday.h"
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

 private slots:
  void on_leftButton_clicked();

  void on_rightButton_clicked();

 private:
  int newsId;
  Ui::StockDashboard *ui;
  QVector<Stock *> stocks;
  StockGraphOneDay *stockGraphOneDay;
  StockGraphThreeDays *stockGraphThreeDays;
  StockGraphOneMonth *stockGraphOneMonth;
  StockGraphSixMonths *stockGraphSixMonths;
};

#endif // STOCKDASHBOARD_H
