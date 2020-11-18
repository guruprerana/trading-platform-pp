#include "trading.h"

void Trading::setSymbol (std::string symbol) {
    this->symbol = symbol;
}

void Trading::setQuantity (double quantity) {
    this->quantity = quantity;
}

void Trading::setStrategy (TradingStrategy strategy) {
    this->strategy = strategy;
}

void Trading::setOrderType (TradingOrderType order_type) {
    this->order_type = order_type;
}

void Trading::setAction (TradingAction action) {
    this->action = action;
}

void Trading::setLimitPrice (double limit_price) {
    this->limit_price = limit_price;
}

void Trading::setTradingTime (time_t trading_time) {
    this->trading_time = trading_time;
}

void Trading::setValuePerQuantity (double value_per_quantity) {
    this->value_per_quantity = value_per_quantity;
}

double Trading::valuation () {
    return value_per_quantity * quantity;
}