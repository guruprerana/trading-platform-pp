#include "portfolio.h"
#include <QVariant>
#include <QJsonArray>

void LoadUp::save(QJsonObject &json) const {
  json.insert("time_stamp", QJsonValue::fromVariant(QVariant(time_stamp)));
  json.insert("quantity", QJsonValue(quantity));
}

void LoadUp::load(const QJsonObject &json) {
  if (json.contains("time_stamp") && json["time_stamp"].isDouble()) {
    time_stamp = json["time_stamp"].toVariant().toLongLong();
  }

  if (json.contains("quantity") && json["quantity"].isDouble()) {
    quantity = json["quantity"].toDouble();
  }
}

qreal Portfolio::valuation() {
  // TO IMPLEMENT
  return 0;
}

void Portfolio::addStockToWatchList(QString &symbol) {
  if (stock_watch_list.indexOf(symbol) >= 0) {
    return;
  }

  stock_watch_list.append(symbol);
}

void Portfolio::removeStockFromWatchList(QString &symbol) {
  int index = stock_watch_list.indexOf(symbol);

  if (index >= 0) {
    stock_watch_list.removeAt(index);
  }
}

void Portfolio::addTradingOrder(TradingOrder *trading_order) {
  trading_order_history.push_back(trading_order);
}

void Portfolio::addLoadUp(LoadUp *load_up) {
  this->current_money += load_up->getQuantity();
  load_up_history.push_back(load_up);
}

void Portfolio::save(QJsonObject &json) const {
  json.insert("id", QJsonValue(id));
  json.insert("current_money", QJsonValue(current_money));

  QJsonArray watchlist = QJsonArray::fromStringList(stock_watch_list);
  json.insert("stock_watch_list", watchlist);

  QJsonArray trading_orders;

  for (int i = 0; i < trading_order_history.size(); ++i) {
    QJsonObject order;
    trading_order_history.at(i)->write(order);
    trading_orders.append(order);
  }

  json.insert("trading_order_history", trading_orders);

  QJsonArray load_ups;

  for (int i = 0; i < load_up_history.size(); ++i) {
    QJsonObject load_up;
    load_up_history.at(i)->save(load_up);
    load_ups.append(load_up);
  }

  json.insert("load_up_history", load_ups);
}

void Portfolio::load(const QJsonObject &json) {
  if (json.contains("id") && json["id"].isString()) {
    id = json["id"].toString();
  }

  if (json.contains("current_money") && json["current_money"].isDouble()) {
    current_money = json["current_money"].toDouble();
  }

  if (json.contains("stock_watch_list") && json["stock_watch_list"].isArray()) {
    QJsonArray symbols = json["stock_watch_list"].toArray();

    for (int i = 0; i < symbols.size(); ++i) {
      if (symbols.at(i).isString()) {
        stock_watch_list.append(symbols.at(i).toString());
      }
    }
  }

  if (json.contains("trading_order_history") &&
      json["trading_order_history"].isArray()) {
    QJsonArray trading_orders = json["trading_order_history"].toArray();

    for (int i = 0; i < trading_orders.size(); ++i) {
      if (trading_orders.at(i).isObject()) {
        TradingOrder *order = new TradingOrder();
        order->read(trading_orders.at(i).toObject());
        trading_order_history.push_back(order);
      }
    }
  }

  if (json.contains("load_up_history") && json["load_up_history"].isArray()) {
    QJsonArray load_ups = json["load_up_history"].toArray();

    for (int i = 0; i < load_ups.size(); ++i) {
      if (load_ups.at(i).isObject()) {
        LoadUp *load_up = new LoadUp();
        load_up->load(load_ups.at(i).toObject());
        load_up_history.push_back(load_up);
      }
    }
  }
}

Portfolio::~Portfolio() {
  for (int i = 0; i < trading_order_history.size(); ++i) {
    delete trading_order_history.value(i);
  }

  for (int i = 0; i < load_up_history.size(); ++i) {
    delete load_up_history.value(i);
  }
}
