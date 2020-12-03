#include "portfolio.h"

qreal Portfolio::valuation() {
  return 0;
}

void Portfolio::addEquitySecurityToWatchList(EquitySecurity es) {
  if (equity_security_watch_list.indexOf(es) == -1) {
    equity_security_watch_list.push_back(es);
  }
}

void Portfolio::removeEquitySecurityFromWatchList(EquitySecurity es) {
  equity_security_watch_list.removeOne(es);
}

void Portfolio::addTradingOrder(TradingOrder trading_order) {
  trading_order_history.push_back(trading_order);
}