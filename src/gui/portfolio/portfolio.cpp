#include "portfolio.h"

#include <algorithm>

Portfolio::Portfolio (double initial_money = 0) {
    this->initial_money = initial_money;
    this->current_money = initial_money;
}

double Portfolio::valuation () {
    return 0;
}

void Portfolio::addEquitySecurityToWatchList (EquitySecurity es) {
    auto it = std::find(equity_security_watch_list.begin(),
                        equity_security_watch_list.end(),
                        es);

    if (it == equity_security_watch_list.end())
        equity_security_watch_list.push_back(es);
}

void Portfolio::removeEquitySecurityFromWatchList (EquitySecurity es) {
    auto it = std::find(equity_security_watch_list.begin(),
                        equity_security_watch_list.end(),
                        es);
                        
    if (it != equity_security_watch_list.end())
        equity_security_watch_list.erase(it);
}

void Portfolio::addTrading (Trading trading) {
    trading_history.push_back(trading);
}