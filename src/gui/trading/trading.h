#ifndef TRADING_H
#define TRADING_H

#include "../security/security.h"

#include <string>

#include <time.h>

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

class Trading {
public:
    double valuation ();
    
    void setSymbol (std::string symbol);
    void setQuantity (double quantity);
    void setStrategy (TradingStrategy strategy);
    void setOrderType (TradingOrderType order_type);
    void setAction (TradingAction action);
    void setLimitPrice (double limit_price);
    
    void setTradingTime (time_t trading_time);
    void setValuePerQuantity (double value_per_quantity);

private:
    std::string symbol;
    double quantity;
    TradingStrategy strategy;
    TradingOrderType order_type;
    TradingAction action;
    double limit_price;

    time_t trading_time;
    double value_per_quantity;
};

#endif // TRADING_H