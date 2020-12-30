#ifndef STRATEGY_H
#define STRATEGY_H

#include "../../components/stock.h"
#include <map>
#include <QList>
#include <QVector>

class Strategy
{
public:
    Strategy();
    Strategy(std::string& strategyName, Stock*& stock, bool& byMinute, std::string& priceType);
    ~Strategy();
    Stock* get_stock();
    std::string get_priceType();
    bool get_byMinute();
    void set_stock(Stock*& other_stock);
    void set_priceType(std::string& other_priceType);
    void set_byMinute(bool& other_byMinute);
    std::map<long, double> get_data(int& nLatestPeriods, int& startingPeriod);

    // void simulate(); might turn out to be useless
    virtual std::tuple<bool, double> calculate_signal();

public:
    void evaluate();
    void compare(Strategy*& other_strategy);

    std::string strategyName;
    Stock* stock;
    bool byMinute;
    std::string priceType;
    QList<double> signalReferences;
    QVector<double> numericSignals;

};

#endif // STRATEGY_H
