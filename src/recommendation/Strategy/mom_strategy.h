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
    std::pair<double,double> get_markups();
    void set_markups(std::pair<double,double>& markups);
    void update_numericSignals(long& depth);
    double firstAuxillary(std::map<long, double> &bars);
    std::tuple<bool, double> calculate_signal();
    std::pair<double,double> markups= std::pair<double,double>(0.025,0.05);
    std::string strategyName = "MOM";



};

#endif // MOM_STRATEGY_H
