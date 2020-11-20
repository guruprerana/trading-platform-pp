/**
 * This header file contains implementations of Portfolio and related classes.
 */

#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "../security/security.h"
#include "../trading_order/trading_order.h"

#include <QLocale>
#include <QVector>

class LoadUp {
public:
    LoadUp ();
    ~LoadUp ();

private:
    qint64 time_stamp;
    qreal quantity;
};

class Portfolio {
public:
    Portfolio ();
    
    qreal valuation ();

    void addEquitySecurityToWatchList (EquitySecurity es);
    void removeEquitySecurityFromWatchList (EquitySecurity es);

    void addTradingOrder (TradingOrder trading_order);

    void addLoadUp (LoadUp load_up);

private:
    qreal current_money;

    QVector<EquitySecurity> equity_security_watch_list;
    QVector<TradingOrder> trading_order_history;
    QVector<LoadUp> load_up_history;
};

#endif // PORTFOLIO_H