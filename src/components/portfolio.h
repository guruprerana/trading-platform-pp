/**
 * This header file contains implementations of Portfolio and related classes.
 */

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "stock.h"
#include "trading_order.h"

#include <QVector>

class LoadUp {
 public:
  LoadUp();
  ~LoadUp();

 private:
  qint64 time_stamp;
  qreal quantity;
};

class Portfolio {
 public:
  Portfolio();

  qreal valuation();

  void addStockToWatchList(Stock st);
  void removeStockFromWatchList(Stock st);

  void addTradingOrder(TradingOrder trading_order);

  void addLoadUp(LoadUp load_up);

 private:
  qreal current_money;

  QVector<Stock> stock_watch_list;
  QVector<TradingOrder> trading_order_history;
  QVector<LoadUp> load_up_history;
};

#endif // PORTFOLIO_H