#include "portfolio.h"

#include <QVariant>
#include <QJsonArray>
#include <QDebug>

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

qreal StockRecord::quantityRecorded() const {
  qreal quantity = 0;

  for (auto &x : record) {
    quantity += x.second;
  }

  return quantity;
}

qreal StockRecord::marketValuePerQuantity() const {
  return stock->getLatestClosedPrice();
}

qreal StockRecord::costBasis() const {
  qreal base_cost = 0;

  for (auto &x : record) {
    base_cost += x.first * x.second;
  }

  return base_cost;
}

qreal StockRecord::valuation() const {
  return marketValuePerQuantity() * quantityRecorded();
}

// DOES NOT TAKE ACCOUNT OF SOLD STOCK
qreal StockRecord::totalGainLoss() const {
  return valuation() - costBasis();
}

void StockRecord::addStock(qreal price, qreal quantity) {
  record.insert(QPair<qreal, qreal>(price, quantity));
}

void StockRecord::removeStock(qreal quantity) {
  if (quantity > quantityRecorded()) {
    return;
  }

  while (quantity > 1e-9) { // basically "while (quantity > 0)"
    Q_ASSERT(!record.empty());

    auto x = *record.begin();
    record.erase(record.begin());

    auto minuend = qMin(quantity, x.second);
    quantity -= minuend;
    x.second -= minuend;

    if (abs(x.second) > 1e-9) {
      record.insert(x);
      // loop should end after this
    }
  }

  return;
}

// Returns the value of the owned stocks
qreal Portfolio::stockValuation() {
  qreal res = 0;

  foreach (StockRecord s, stock_records) {
    res += s.valuation();
  }

  return res;
}

// Returns the total value of the portfolio
qreal Portfolio::valuation() {
  return stockValuation() + current_money;
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
  QString symbol = trading_order->getSymbol();

  // init if not exist
  if (!stock_records.contains(symbol)) {
    qDebug() << "did not exists before" << endl;
    stock_records[symbol] = StockRecord(symbol);
  }

  qDebug() << "current tradingorder size" << trading_order_history.size() <<
           endl;
  qDebug() << stock_records[symbol].quantityRecorded() << endl;

  // main code
  if (trading_order->getAction() == TradingOrder::TradingAction::Buy) {
    qDebug() << "we buy" << endl;
    qreal current_price = stock_records[symbol].stock->getLatestClosedPrice();
    qDebug() << "current_price: " << current_price << endl;
    stock_records[symbol].addStock(current_price, trading_order->getQuantity());
    trading_order_history.push_back(trading_order);
    qDebug() << "trading_order_history size: " << trading_order_history.size() <<
             endl;

    // update the current money
    this->current_money = this->current_money - (current_price *
                          trading_order->getQuantity());
  } else if (trading_order->getAction() == TradingOrder::TradingAction::Sell) {

  } else {  // do not need to implement this case (SellShort)
    return;
  }
}

void Portfolio::addLoadUp(LoadUp *load_up) {
  this->current_money += load_up->getQuantity();
  load_up_history.push_back(load_up);
}

void Portfolio::computeRecordFromHistory() {
  stock_records = QHash<QString, StockRecord>();

  qDebug() << "computeRecordFromHistory"  << ' ' << trading_order_history.size()
           << endl;

  for (auto &trading_order : trading_order_history) {
    QString symbol = trading_order->getSymbol();
    qDebug() << symbol << ' ' << trading_order->getQuantity() << endl;

    // init if not exist
    if (!stock_records.contains(symbol)) {
      stock_records[symbol] = StockRecord(symbol);
    }

    // main code
    if (trading_order->getAction() == TradingOrder::TradingAction::Buy) {
      qreal current_price = stock_records[symbol].stock->getLatestClosedPrice();
      stock_records[symbol].addStock(current_price, trading_order->getQuantity());
    } else if (trading_order->getAction() == TradingOrder::TradingAction::Sell) {

    } else {  // do not need to implement this case (SellShort)
      return;
    }
  }
}

QVector<QString> Portfolio::currentOwnedStock() {
  QHash<QString, StockRecord>::const_iterator it = stock_records.constBegin();

  QSet<QString> owned;

  while (it != stock_records.constEnd()) {
    if (it.value().quantityRecorded() > 1e-9) { // the same as > 0
      owned.insert(it.key());
    }

    ++it;
  }

  QVector <QString> owned_qvector;

  foreach (QString v, owned) {
    owned_qvector.push_back(v);
  }

  return owned_qvector;
}

qreal Portfolio::getQuantityLeft(QString symbol) {
  if (!stock_records.contains(symbol)) {
    return 0;
  }

  return stock_records.value(symbol).quantityRecorded();
}

qreal Portfolio::getQuantityLeft(std::string symbol) {
  return getQuantityLeft(helper::toQString(symbol));
}

// Return the value of all quantity owned, not per quantity
qreal Portfolio::getMarketValue(QString symbol) {
  if (!stock_records.contains(symbol)) {
    return 0;
  }

  return stock_records.value(symbol).valuation();
}

qreal Portfolio::getMarketValue(std::string symbol) {
  return getMarketValue(helper::toQString(symbol));
}

qreal Portfolio::getCostBasis(QString symbol) {
  if (!stock_records.contains(symbol)) {
    return 0;
  }

  return stock_records.value(symbol).costBasis();
}

qreal Portfolio::getCostBasis(std::string symbol) {
  return getCostBasis(helper::toQString(symbol));
}

qreal Portfolio::getTotalGainLoss(QString symbol) {
  if (!stock_records.contains(symbol)) {
    return 0;
  }

  return stock_records.value(symbol).totalGainLoss();
}

qreal Portfolio::getTotalGainLoss(std::string symbol) {
  return getTotalGainLoss(helper::toQString(symbol));
}

qreal Portfolio::getPercentOfAccount(QString symbol) {
  if (!stock_records.contains(symbol)) {
    return 0;
  }

  return stock_records.value(symbol).valuation() / valuation() * 100;
}

qreal Portfolio::getPercentOfAccount(std::string symbol) {
  return getPercentOfAccount(helper::toQString(symbol));
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
