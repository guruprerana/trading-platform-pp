#ifndef LR_STRATEGY_H
#define LR_STRATEGY_H
#include "../../components/stock.h"
#include "strategy.h"
#include <map>

using namespace std;

class LRStrategy: public Strategy
{
public:
    LRStrategy(Stock*& stock,bool& byMinute, std::string& priceType);
    ~LRStrategy();
    void update_numericSignals(long& depth);
    std::tuple<bool, double> calculate_signal();
    std::string strategyName = "LR";
    double compute_average_key(std::map<long, double> &bars);
    double compute_average_value(std::map<long, double> &bars);
    std::tuple<bool, double> auxiliary_linear_regression(std::map<long, double> &bars);



};
#endif // LR_STRATEGY_H
