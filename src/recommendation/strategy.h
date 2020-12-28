#ifndef STRATEGY_H
#define STRATEGY_H

#include "../components/stock.h"
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
using std::string;
using std::map;

class Strategy
{
public:
    Strategy();
    Strategy(std::string strategy_name, Stock *stock, bool data_by_minute, std::string price_type);
    ~Strategy();
    void set_stock(Stock* stock);
    Stock* get_stock();
    std::string get_name();
    std::string get_price_type();
    std::map<long, double> get_data(int N, int k = 0);
    double calculate_sma(std::map<long, double> &bars);
    double calculate_ema(std::map<long, double> &bars);
    int auxiliary_momentum(std::map<int, double> &cache);
    bool exponential_moving_average();
    double compute_average_value(std::map<long, double> &bars);
    double compute_average_key(std::map<long, double> &bars);
    std::tuple<bool, double> auxiliary_linear_regression(std::map<long, double> &bars);
    bool linear_regression();
    std::tuple<bool, double> momentum();



protected:
    std::tuple<bool, double> calculate_signals();
    // The heart of each strategy, which we have already implemented within subteams

    /* virtual */ void simulate();


    // more advanced member functions - to be implemented if time permits

    void evaluate(); // Report technical assessment on strategy's performance
    void compare(Strategy* other_strategy); // compare strategies with criteria list

    // Data members
    std::string strategy_name;
    Stock* stock; // stock under consideration
    bool data_by_minute;
    std::string price_type;// price_type is a lower case string in ['o','c','h','l','v']
    std::string str1 = "EMA";
    std::string str2 = "MOM";
    std::string str3 = "LR";




};

#endif // STRATEGY_H
