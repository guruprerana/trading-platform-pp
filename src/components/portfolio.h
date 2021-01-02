/**
 * This header file contains implementations of Portfolio and related classes.
 */

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "stock.h"
#include "trading_order.h"

#include <QVector>
#include <QJsonObject>
#include <QStringList>

class LoadUp {
 public:
  LoadUp() {};
  ~LoadUp() {};

  void load(const QJsonObject &json);
  void save(QJsonObject &json) const;

  qreal getQuantity() const {
    return quantity;
  }

 private:
  qint64 time_stamp;
  qreal quantity;
};

class Portfolio {
 public:
  Portfolio() {};
  Portfolio(QString id_n, qreal amount, QStringList watchlist) : id(id_n),
    current_money(amount), stock_watch_list(watchlist) {};
  ~Portfolio();

  qreal valuation();

  QString getId() const {
    return id;
  }
  QStringList &getWatchList() {
    return stock_watch_list;
  }

  void addStockToWatchList(QString &symbol);
  void removeStockFromWatchList(QString &symbol);

  void addTradingOrder(TradingOrder *trading_order);

  void addLoadUp(LoadUp *load_up);

  void load(const QJsonObject &json);
  void save(QJsonObject &json) const;

 private:
  QString id;

  qreal current_money;

  QStringList stock_watch_list;
  QVector<TradingOrder *> trading_order_history;
  QVector<LoadUp *> load_up_history;
};

#endif // PORTFOLIO_H
