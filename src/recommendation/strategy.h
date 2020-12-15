#ifndef STRATEGY_H
#define STRATEGY_H

#include <stock.h>
#include <api.h>
#include <QtWidgets>
#include <QtCharts/QtCharts>
#include <iostream>

class Strategy
{
public:
    Strategy();

    Strategy(char& strategy_name, Stock*& stock, bool data_by_minute, std::string price_type); // stock = stock to be chosen by user

    ~Strategy();

    void set_stock(Stock* stock);
    std::vector<Stock*> get_stock();
    std::string get_name();
    std::string get_price_type();
    std::map<long, double> get_data(int N, int k =0);
    bool calculate_sma(map<long, double> &bars);
    bool calculate_ema(map<long, double> &bars);
    int auxiliary_momentum(map<int, double> &cache, map<int, double> &cache_date, double moment, map<long, double> bars);
    bool exponential_moving_average();
    double compute_average_value(map<long, double> &bars);
    double compute_average_key(map<long, double> &bars);
    double auxiliary_linear_regression(map<long, double> &bars);
    bool linear_regression();
    std::tuple<bool, double> momentum();



protected:
    std::tuple<bool, double> calculate_signals();
    // The heart of each strategy, which we have already implemented within subteams

    /* virtual */ void simulate();

    // Plot the graphs associated with the strategy
    // Add BUY/SELL signal points



    // more advanced member functions - to be implemented if time permits

    void evaluate(); // Report technical assessment on strategy's performance
    void compare(Strategy* other_strategy); // compare strategies with criteria list

    // Data members
    std::string strategy_name;
    Stock*& stock; // stock under consideration
    bool data_by_minute;
    std::string price_type;// price_type is a lower case string in ['o','c','h','l','v']


};

#endif // STRATEGY_H
