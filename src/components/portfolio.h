/**
 * This header file contains implementations of Portfolio and related classes.
 */

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "stock.h"
#include "trading_order.h"
#include "helper/helper.h"

#include <QSet>
#include <QVector>
#include <QJsonObject>
#include <QStringList>

#include <set>
#include <string>

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

// This class stores quantity of a stock, and the price when bought it
// We store them in a set of pair <buying price - quantity>
// AFTER SELL A PART OF STOCK WE DO NOT KEEP TRACK THEM
class StockRecord {
 public:
  StockRecord(std::string s): stock(new Stock(s)) {};
  StockRecord(QString s): stock(new Stock(helper::toStdString(s))) {};
  StockRecord(Stock *s): stock(s) {};
  ~StockRecord() {};

  qreal quantityRecorded() const;
  qreal baseCost() const;
  qreal valuation() const;
  qreal totalGainLoss() const;
  void addStock(qreal price, qreal quantity);
  void removeStock(qreal quantity);

  Stock *stock;
 private:
  std::multiset <QPair<qreal, qreal>> record; // first = price, second = quantity

};

class Portfolio {
 public:
  Portfolio() {};
  Portfolio(QString id_n, qreal amount, QStringList watchlist) : id(id_n),
    current_money(amount), stock_watch_list(watchlist) {};
  ~Portfolio();

  qreal stockValuation();
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

  QVector <QString> currentOwnedStock();
  qreal getQuantityLeft(QString symbol);
  qreal getQuantityLeft(std::string symbol);
  qreal getBaseCost(QString symbol);
  qreal getBaseCost(std::string symbol);
  qreal getTotalGainLoss(QString symbol);
  qreal getTotalGainLoss(std::string symbol);
  qreal getPercentOfAccount(QString symbol);
  qreal getPercentOfAccount(std::string symbol);

 private:
  QString id;

  qreal current_money;

  QStringList stock_watch_list;
  QVector<TradingOrder *> trading_order_history;
  QVector<LoadUp *> load_up_history;
  QHash <QString, StockRecord> stock_records;
};

#endif // PORTFOLIO_H
