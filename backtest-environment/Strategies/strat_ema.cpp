
// CSE201-2020 Object-Oriented Programming in C++
// Trading Platform Project - Machine Learning sub-team 

// Implementation of an Exponential Moving Average(EMA) Strategy
// Added by Frédéric Marcel Tchouli on 14/11/2020
  

#include "strategiesheader.hpp"
#include <stdlib.h> //rand()
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

// Calculate Exponential Moving Average
double calculate_ema(map<long, double> &bars) {
    assert(!bars.empty());
    double e_MovingAverage = 0;
    int weight_factor = 0;
    double smoothing_parameter = 0.1; // 0.45 + (rand()/RAND_MAX)/10
    for (auto &it : bars) {
        e_MovingAverage += smoothing_parameter*(std::pow(1-smoothing_parameter,weight_factor))*(it.second); 
        weight_factor += 1;
    }
    return e_MovingAverage;
}


// Update map of bought symbols
void MainStrategy::calculate_signals(MarketEvent i_event) {
    
    // LONG any symbol whose bar is updated by marketevent
    for (int i=0; i < symbol_list->size(); i++) {
        string symbol = (*symbol_list)[i];
        map<string, map<long, double>> LongEMA_bars = bars->get_latest_bars(symbol, 49);
         if (LongEMA_bars.empty()) continue;
        map<string, map<long, double>> ShortEMA_bars = bars->get_latest_bars(symbol, 19);
        if (ShortEMA_bars.empty()) continue;
        double LongEMA = calculate_ema(LongEMA_bars["open"]);
        double ShortEMA = calculate_ema(ShortEMA_bars["open"]);
        if (ShortEMA > LongEMA && !bought[symbol]) {
            events->push_back(new SignalEvent(symbol, ShortEMA_bars["open"].rbegin()->first, 1.0));
            bought[symbol] = true;
        }
        else if (LongEMA >= ShortEMA && bought[symbol]) {
            events->push_back(new SignalEvent(symbol, ShortEMA_bars["open"].rbegin()->first, -1.0));
            bought[symbol] = false;
        }    
    }
}
