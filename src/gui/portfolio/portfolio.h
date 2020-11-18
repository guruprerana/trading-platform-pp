/**
 * This header file contains implementations of Portfolio class
 */

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "../security/security.h"
#include "../trading/trading.h"

#include <vector>

class Portfolio {
public:
    Portfolio (double initial_money);
    
    double valuation ();

    void addEquitySecurityToWatchList (EquitySecurity es);
    void removeEquitySecurityFromWatchList (EquitySecurity es);

    void addTrading (Trading trading);
    
private:
    double initial_money;
    double current_money;

    std::vector<EquitySecurity> equity_security_watch_list;
    std::vector<Trading> trading_history;
};

#endif // PORTFOLIO_H