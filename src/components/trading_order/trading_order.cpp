#include "trading_order.h"

void TradingOrder::setSymbol (QString symbol) {
    this->symbol = symbol;
}

void TradingOrder::setQuantity (qreal quantity) {
    this->quantity = quantity;
}

void TradingOrder::setStrategy (TradingStrategy strategy) {
    this->strategy = strategy;
}

void TradingOrder::setOrderType (TradingOrderType order_type) {
    this->order_type = order_type;
}

void TradingOrder::setAction (TradingAction action) {
    this->action = action;
}

void TradingOrder::setLimitPrice (qreal limit_price) {
    this->limit_price = limit_price;
}

void TradingOrder::setTradingTime (qint64 trading_order_time_stamp) {
    this->trading_order_time_stamp = trading_order_time_stamp;
}

void TradingOrder::setValuePerQuantity (qreal value_per_quantity) {
    this->value_per_quantity = value_per_quantity;
}

double TradingOrder::valuation () {
    return value_per_quantity * quantity;
}