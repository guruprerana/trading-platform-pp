#ifndef MOM_STRATEGY_H
#define MOM_STRATEGY_H

#include "../../components/stock.h"
#include "strategy.h"
#include <map>

using namespace std;

class MOMStrategy: public Strategy
{
public:
    MOMStrategy(Stock*& stock,bool& byMinute, std::string& priceType);
    ~MOMStrategy();
    void update_numericSignals(long& depth);
    int auxiliary_momentum(std::map<int, double> &cache);
    std::tuple<bool, double> calculate_signal();
    double calculate_sma(std::map<long, double> &bars);
    std::string strategyName = "MOM";




};

#endif // MOM_STRATEGY_H
