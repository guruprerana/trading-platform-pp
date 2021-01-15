#ifndef TRADINGORDER_H
#define TRADINGORDER_H

#include "stock.h"

#include <QJsonObject>
#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>
#include <QString>

class TradingOrder {
  Q_GADGET

 public:
  enum TradingAction {
    Buy,
    Sell,
    SellShort
  };
  Q_ENUM(TradingAction)

  enum TradingStrategy {
    ETF,
    Call,
    Put
  };
  Q_ENUM(TradingStrategy)

  enum TradingOrderType {
    MarketOrder,
    Limit,
    Stop,
    StopLimit,
    TrailingStop
  };
  Q_ENUM(TradingOrderType)

  enum TradingTiming {
    DayOnly,
    GoodUntilCancelled,
    FillorKill,
    ImmediateorCancel,
    ExtendedHours
  };
  Q_ENUM(TradingTiming)

  TradingOrder();

  double valuation();

  void setSymbol(QString symbol);
  void setQuantity(qreal quantity);
  void setStrategy(TradingStrategy strategy);
  void setOrderType(TradingOrderType order_type);
  void setAction(TradingAction action);
  void setTiming(TradingTiming timing);
  void setLimitPrice(qreal limit_price);

  void setTradingTime(qint64 trading_order_time_stamp);
  void setValuePerQuantity(qreal value_per_quantity);

  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;

 private:
  QString symbol;
  qreal quantity;
  TradingStrategy strategy;
  TradingOrderType order_type;
  TradingAction action;
  TradingTiming timing;
  qreal limit_price;

  qint64 trading_order_time_stamp;
  qreal value_per_quantity;
};

#endif // TRADINGORDER_H
