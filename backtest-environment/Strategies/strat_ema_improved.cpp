// Implementation of Exponential Moving Average Strategy
#include "strategiesheader.hpp"
#include <stdlib.h>
#include <math.h>
#ifndef ptr_vector
#include <boost/ptr_container/ptr_vector.hpp>
#endif

// Initialize strategy
MainStrategy::MainStrategy(HistoricalCSVDataHandler* i_bars, boost::ptr_vector<Event>*i_events) {

    // Set instance variables
    bars = i_bars;
    events = i_events;
    *bars->symbol_list = {string("AAPL")};
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

// Calculate Exponential Moving Average
double calculate_ema(map<long, double> &bars) {
    assert(!bars.empty());
    double e_MovingAverage = 0;
    double smoothing_parameter = 0.4; //decay factor of terms in Moving Average
    int weight_factor = 0; // degree of the smoothing_parameter for a given summand
    for (auto &it : bars) {
        e_MovingAverage += smoothing_parameter * (std::pow((1-smoothing_parameter),weight_factor)) * it.second;
        weight_factor += 1;
    }
    return e_MovingAverage;
}

// Update map of bought symbols
void MainStrategy::calculate_signals(MarketEvent i_event) {

    // LONG any symbol whose bar is updated by marketevent
    for (int i=0; i < symbol_list->size(); i++) {
        string symbol = (*symbol_list)[i];
        map<string, map<long, double>> bars_11 = bars->get_latest_bars(symbol,11);
        if (bars_11.empty()) continue; // check if empty and include more bars
        map<string, map<long, double>> bars_6 = bars->get_latest_bars(symbol,6);
        if (bars_11.empty()) continue; // check if empty and include more bars

        double ema_11 = calculate_ema(bars_11["open"]); // Longer Moving Average
        double ema_06 = calculate_ema(bars_6["open"]);  // Shorter Moving Average
        double markup = 0.05;// markup introduces anticipation into our strategy:
        if (ema_06 > (1-markup)*ema_11 && !bought[symbol]) {
            events->push_back(new SignalEvent(symbol, bars_6["open"].rbegin()->first, 1.0));
            bought[symbol] = true;
        }
        else if (ema_11 > (1+markup)*ema_06 && bought[symbol]) {
            events->push_back(new SignalEvent(symbol, bars_6["open"].rbegin()->first, -1.0));
            bought[symbol] = false;
        }
    }
}
