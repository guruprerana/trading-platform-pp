#include "trading_order.h"
#include <QVariant>

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

void TradingOrder::save(QJsonObject &json) const {
  json.insert("symbol", QJsonValue(symbol));
  json.insert("quantity", QJsonValue(quantity));
  json.insert("limit_price", QJsonValue(limit_price));
  json.insert("trading_order_time_stamp", QJsonValue(trading_order_time_stamp));
  json.insert("value_per_quantity", QJsonValue(value_per_quantity));

  if (strategy == TradingStrategy::StockETF) {
    json.insert("strategy", "StockETF");
  } else if (strategy == TradingStrategy::CallOption) {
    json.insert("strategy", "CallOption");
  } else if (strategy == TradingStrategy::PutOption) {
    json.insert("strategy", "PutOption");
  }

  if (order_type == TradingOrderType::MarketOrder) {
    json.insert("order_type", "MarketOrder");
  } else if (order_type == TradingOrderType::Limit) {
    json.insert("order_type", "Limit");
  } else if (order_type == TradingOrderType::Stop) {
    json.insert("order_type", "Stop");
  } else if (order_type == TradingOrderType::StopLimit) {
    json.insert("order_type", "StopLimit");
  } else if (order_type == TradingOrderType::TrailingStop) {
    json.insert("order_type", "TrailingStop");
  }

  if (action == TradingAction::Buy) {
    json.insert("action", "Buy");
  } else if (action == TradingAction::Sell) {
    json.insert("action", "Sell");
  } else if (action == TradingAction::SellShort) {
    json.insert("action", "SellShort");
  }
}

void TradingOrder::load(const QJsonObject &json) {
  if (json.contains("symbol") && json["symbol"].isString()) {
    symbol = json["symbol"].toString();
  }

  if (json.contains("quantity") && json["quantity"].isDouble()) {
    quantity = json["quantity"].toDouble();
  }

  if (json.contains("limit_price") && json["limit_price"].isDouble()) {
    limit_price = json["limit_price"].toDouble();
  }

  if (json.contains("trading_order_time_stamp") &&
      json["trading_order_time_stamp"].isDouble()) {
    trading_order_time_stamp =
      json["trading_order_time_stamp"].toVariant().toLongLong();
  }

  if (json.contains("value_per_quantity") &&
      json["value_per_quantity"].isDouble()) {
    value_per_quantity = json["value_per_quantity"].toDouble();
  }

  if (json.contains("strategy") && json["strategy"].isString()) {
    QString strategy_json = json["strategy"].toString();

    if (strategy_json == QString("StockETF")) {
      strategy = TradingStrategy::StockETF;
    } else if (strategy_json == QString("CallOption")) {
      strategy = TradingStrategy::CallOption;
    } else if (strategy_json == QString("PutOption")) {
      strategy = TradingStrategy::PutOption;
    }
  }

  if (json.contains("order_type") && json["order_type"].isString()) {
    QString order_type_json = json["order_type"].toString();

    if (order_type_json == QString("MarketOrder")) {
      order_type = TradingOrderType::MarketOrder;
    } else if (order_type_json == QString("Limit")) {
      order_type = TradingOrderType::Limit;
    } else if (order_type_json == QString("Stop")) {
      order_type = TradingOrderType::Stop;
    } else if (order_type_json == QString("StopLimit")) {
      order_type = TradingOrderType::StopLimit;
    } else if (order_type_json == QString("TrailingStop")) {
      order_type = TradingOrderType::TrailingStop;
    }
  }

  if (json.contains("action") && json["action"].isString()) {
    QString action_json = json["action"].toString();

    if (action_json == QString("Buy")) {
      action = TradingAction::Buy;
    } else if (action_json == QString("Sell")) {
      action = TradingAction::Sell;
    } else if (action_json == QString("SellShort")) {
      action = TradingAction::SellShort;
    }
  }
}
