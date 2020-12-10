#include "trading_order.h"

TradingOrder::TradingOrder() {
  trading_order_time_stamp = -1;
}

void TradingOrder::setSymbol(QString symbol) {
  this->symbol = symbol;
}

void TradingOrder::setQuantity(qreal quantity) {
  this->quantity = quantity;
}

void TradingOrder::setStrategy(TradingStrategy strategy) {
  this->strategy = strategy;
}

void TradingOrder::setOrderType(TradingOrderType order_type) {
  this->order_type = order_type;
}

void TradingOrder::setAction(TradingAction action) {
  this->action = action;
}

void TradingOrder::setTiming(TradingTiming timing) {
  this->timing = timing;
}

void TradingOrder::setLimitPrice(qreal limit_price) {
  this->limit_price = limit_price;
}

void TradingOrder::setTradingTime(qint64 trading_order_time_stamp) {
  this->trading_order_time_stamp = trading_order_time_stamp;
}

void TradingOrder::setValuePerQuantity(qreal value_per_quantity) {
  this->value_per_quantity = value_per_quantity;
}

double TradingOrder::valuation() {
  return value_per_quantity * quantity;
}

void TradingOrder::read(const QJsonObject &json) {
  if (json.contains("symbol") && json["symbol"].isString()) {
    symbol = json["symbol"].toString();
  }

  if (json.contains("quantity") && json["quantity"].isDouble()) {
    quantity = json["quantity"].toInt();
  }

  if (json.contains("strategy") && json["strategy"].isString()) {
    symbol = json["strategy"].toString();
  }

  if (json.contains("order_type") && json["order_type"].isString()) {
    symbol = json["order_type"].toString();
  }

  if (json.contains("action") && json["action"].isString()) {
    symbol = json["action"].toString();
  }

  if (json.contains("limit_price") && json["limit_price"].isDouble()) {
    symbol = json["limit_price"].toDouble();
  }

  if (json.contains("trading_order_time_stamp") &&
      json["trading_order_time_stamp"].isDouble()) {
    symbol = json["trading_order_time_stamp"].toInt();
  }

  if (json.contains("value_per_quantity") &&
      json["value_per_quantity"].isDouble()) {
    symbol = json["value_per_quantity"].toDouble();
  }
}

template<typename QEnum>
QString QtEnumToString(const QEnum value) {
  return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

void TradingOrder::write(QJsonObject &json) const {
  json["symbol"] = symbol;
  json["quantity"] = quantity;
  json["strategy"] = QtEnumToString<TradingOrder::TradingStrategy>(strategy);
  json["order_type"] = QtEnumToString<TradingOrder::TradingOrderType>(order_type);
  json["action"] = QtEnumToString <TradingOrder::TradingAction> (action);
  json["limit_price"] = limit_price;
  json["trading_order_time_stamp"] = trading_order_time_stamp;
  json["value_per_quantity"] = value_per_quantity;
}
