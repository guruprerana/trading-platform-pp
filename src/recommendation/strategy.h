#ifndef STRATEGY_H
#define STRATEGY_H
#include "../components/stock.h"
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <QVector>
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

    //Handling maps of data
    void set_map_six_months();
    std::map<long, double> get_map_six_months();
    std::map<int, double> get_desired_map(int N, int k = 0); //Returns a map with only the elements we need from the data member map_data

    //Auxiliary functions use to make recommandation
    double calculate_sma(std::map<int, double> &bars);
    double calculate_ema(std::map<int, double> &bars);
    int auxiliary_momentum(std::map<int, double> &cache);
    bool exponential_moving_average();
    double compute_average_value(std::map<int, double> &bars);
    double compute_average_key(std::map<int, double> &bars);
    std::tuple<double, double> auxiliary_linear_regression(std::map<int, double> &bars);
    bool linear_regression();
    std::tuple<bool, double> momentum();

    //Makes the recommandation : buy or sell or nothing and the percentage
    std::tuple<bool, double> calculate_signals();

    //Returns the vectors used for the plots
    std::tuple<QVector<long>, QVector<double>> simulate();



protected:
    // Data members
    std::string strategy_name;
    Stock* stock; // stock under consideration
    bool data_by_minute;
    std::string price_type;// price_type is a lower case string in ['o','c','h','l','v']
    std::string str1 = "EMA";
    std::string str2 = "MOM";
    std::string str3 = "LR";
    std::map<long, double> map_six_months; //map containing the data over the last 6 months

};


#endif // STRATEGY_H
