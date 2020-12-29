#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QTimer>
#include "stockgraphoneday.h"
#include "stockgraphthreedays.h"
#include "stockgraphonemonth.h"
#include "stockgraphsixmonths.h"
#include "watchlistcard.h"
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
  void displayNews();

 private slots:
  void realtimeUpdateStocks();
  void changeCurrentStock(int stockId);
  void on_leftButton_clicked();
  void on_rightButton_clicked();

 private:
  int newsId;
  int currentUpdateStockId;
  int currentStockId;
  bool loadedStocks;
  Ui::HomePage *ui;
  QVector<WatchlistCard *> watchlistCards;
  QVector<Stock *> watchlistStocks;
//  QVector<StockGraphOneDay *> graphsOneDay;
//  QVector<StockGraphThreeDays *> graphsThreeDays;
//  QVector<StockGraphOneMonth *> graphsOneMonth;
//  QVector<StockGraphSixMonths *> graphsSixMonths;
  StockGraphOneDay *stockGraphOneDay;
  StockGraphThreeDays *stockGraphThreeDays;
  StockGraphOneMonth *stockGraphOneMonth;
  StockGraphSixMonths *stockGraphSixMonths;
  QTimer timer;
};

#endif // HOMEPAGE_H
