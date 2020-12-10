#include "portfolio.h"

qreal Portfolio::valuation() {
  return 0;
}

void Portfolio::addStockToWatchList(Stock st) {
  // if (stock_watch_list.indexOf(st) == -1) {
  //   stock_watch_list.push_back(st);
  // }
}

void Portfolio::removeStockFromWatchList(Stock st) {
  // stock_watch_list.removeOne(st);
}

void Portfolio::addTradingOrder(TradingOrder trading_order) {
  trading_order_history.push_back(trading_order);
}