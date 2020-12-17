#ifndef TRADINGORDER_H
#define TRADINGORDER_H

#include "../stock.h"
#include "../serializable.h"

#include <QDateTime>
#include <QString>

enum TradingAction {
  Buy,
  Sell,
  SellShort
};

enum TradingStrategy {
  StockETF,
  CallOption,
  PutOption
};

enum TradingOrderType {
  MarketOrder,
  Limit,
  Stop,
  StopLimit,
  TrailingStop
};

enum TradingTiming {
  DayOnly,
  GoodUntilCancelled,
  FillorKill,
  ImmediateorCancel,
  ExtendedHours
};

class TradingOrder {
 public:
  TradingOrder() {};
  ~TradingOrder() {};

  double valuation();

  void setSymbol(QString symbol);
  void setQuantity(qreal quantity);
  void setStrategy(TradingStrategy strategy);
  void setOrderType(TradingOrderType order_type);
  void setAction(TradingAction action);
  void setLimitPrice(qreal limit_price);

  void setTradingTime(qlonglong trading_order_time_stamp);
  void setValuePerQuantity(qreal value_per_quantity);

  void load(const QJsonObject &json);
  void save(QJsonObject &json) const;

 private:
  QString symbol;
  qreal quantity;
  TradingStrategy strategy;
  TradingOrderType order_type;
  TradingAction action;
  qreal limit_price;

  qlonglong trading_order_time_stamp;
  qreal value_per_quantity;
};

#endif // TRADINGORDER_H
