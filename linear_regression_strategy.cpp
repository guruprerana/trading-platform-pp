//implementation of the linear regression strategy

#include "strategiesheader.hpp"
#include <math.h> 
#ifndef ptr_vector
#include <boost/ptr_container/ptr_vector.hpp>
#endif

// Initialize strategy
MainStrategy::MainStrategy(HistoricalCSVDataHandler* i_bars, boost::ptr_vector<Event>*i_events) {

    // Set instance variables
    bars = i_bars;
    events = i_events;
    *bars->symbol_list = {string("GS"),string("AAPL"), string("CAT")};
    symbol_list = bars->symbol_list;

    // Set custom strategy variables
    // Need to instantiate map bought in header file
    bought = calculate_initial_bought();
}

// Placeholder initializer
MainStrategy::MainStrategy()=default;

// Create map of bought symbols
map<string, bool> MainStrategy::calculate_initial_bought() {
    bought = {};
    for (int i=0; i < symbol_list->size(); i++) {
        bought[(*symbol_list)[i]] = false; }
    return bought;
}

double compute_average_key(map<long, double> &bars){
    double key_average = 0;
    for (auto &item : bars) {
            key_average += item.first;
        }
    return (key_average/bars.size());
}

double compute_average_value(map<long, double> &bars){
    double value_average = 0;
    for (auto &item : bars) {
            value_average += item.second;
        }
    return (value_average/bars.size());
}

map<long, double> calculate_linear_regression(map<long, double> &bars){ // use ordinary least square method
    assert(!bars.empty());
    double value_average= compute_average_value(bars);
    double key_average= compute_average_key(bars);
    double ss_xy = 0;
    double ss_xx = 0;
    for (auto &item : bars) {
            ss_xx += (item.first- key_average)* (item.second - value_average);
            ss_xy += pow(item.first- key_average, 2);
        }
    double slope = ss_xx/ss_xy;
    double intercept = value_average -slope* key_average;

    for (auto &item : bars) {
            item.second = item.first * slope + intercept; // fitted plot
        }
    return bars; 
}

// Update map of bought symbols
void MainStrategy::calculate_signals(MarketEvent i_event) {
    // LONG any symbol whose bar is updated by marketevent
    for (int i=0; i < symbol_list->size(); i++) {
        string symbol = (*symbol_list)[i];
        map<string, map<long, double>> newbars = bars->get_latest_bars(symbol,100 ); // n latest bars to new bars
        map<long, double> fit_bars = calculate_linear_regression(newbars["open"]);
        if (!newbars.empty() && newbars["open"].begin()->second > 0.01) {
            if (!bought[symbol]) {

                // (symbol, time, type=LONG, SHORT or EXIT)
                events->push_back(new SignalEvent(symbol, fit_bars.begin()->first, 0.1));
                bought[symbol] = true;
            }
        }
    }
 }


