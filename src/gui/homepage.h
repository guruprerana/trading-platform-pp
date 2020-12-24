#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "stockgraphoneday.h"
#include "stockgraphthreedays.h"
#include "stockgraphonemonth.h"
#include "stockgraphsixmonths.h"
#include "components/stock.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget {
  Q_OBJECT

 public:
  explicit HomePage(QWidget *parent = nullptr);
  ~HomePage();

  void updateWatchlistStocks(QVector<Stock *> other_watchlistStocks);

 private slots:
  void on_leftButton_clicked();

  void on_rightButton_clicked();

 private:
  int newsId;
  Ui::HomePage *ui;
  QVector<Stock *> watchlistStocks;
  StockGraphOneDay *stockGraphOneDay;
  StockGraphThreeDays *stockGraphThreeDays;
  StockGraphOneMonth *stockGraphOneMonth;
  StockGraphSixMonths *stockGraphSixMonths;
};

#endif // HOMEPAGE_H
