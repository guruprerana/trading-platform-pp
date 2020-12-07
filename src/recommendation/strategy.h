#ifndef STRATEGY_H
#define STRATEGY_H

#include <stock.h>
#include <api.h>
#include <QtWidgets>
#include <QtCharts/QtCharts>
#include <vector>

class Strategy
{
public:
    Strategy();

    Strategy(char& strategy_name, std::vector<Stock*> stocks_vector, bool data_by_minute, std::string price_type); // stock = stock to be chosen by user

    ~Strategy();

    void set_stock(Stock* stock);
    std::vector<Stock*> get_stock();
    std::string get_name();
    map<string, bool> calculate_initial_bought();
    bool exponential_moving_average();
    bool linear_regression();
    bool momentum();



protected:
    virtual void calculate_signals();
    // The heart of each strategy, which we have already implemented within subteams

    /* virtual */ void simulate();

    // Plot the graphs associated with the strategy
    // Add BUY/SELL signal points



    // more advanced member functions - to be implemented if time permits

    void evaluate(); // Report technical assessment on strategy's performance
    void compare(Strategy* other_strategy); // compare strategies with criteria list

    // Data members
    std::string strategy_name;
    Stock* stock; // stock under consideration
    bool data_by_minute;
    std::string price_type;// price_type is a lower case string in { 'o','c','h','l'} 
    //indicating if we consider opening,closing,highest, lowest prices


};

#endif // STRATEGY_H
