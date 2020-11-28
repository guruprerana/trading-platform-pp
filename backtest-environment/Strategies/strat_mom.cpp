#include "strategiesheader.hpp"

#ifndef ptr_vector
#include <boost/ptr_container/ptr_vector.hpp>
#endif

// Initialize strategy
MainStrategy::MainStrategy(HistoricalCSVDataHandler* i_bars, boost::ptr_vector<Event>*i_events) {
    
    // Set instance variables
    bars = i_bars;
    events = i_events;
    *bars->symbol_list = {string("SPY")};
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

// Calculate Simple Moving Average 
double MainStrategy::calculate_sma(map<long, double> &bars) {
    assert(!bars.empty());
    double sum = 0;
    for (auto &it : bars) {
        sum += it.second;
    }
    return sum / bars.size();
}


map<int, double> cache;


int momentum(&double cache, double moment){
//1-full, 0-sell, -1-perc
    if (cache.size()<3)
    {
        cache.insert(pair<int, double>(1, moment));
        if (moment>=1)
            return 1
        return 0

    }

    if(moment<1)
        return 0

    double diff1=cache.at(3)-cache.at(2)
    double diff2=cache.at(1)-moment
    double temp= cache.at(2)
    cache.at(2) = cache.at(1);
    cache.at(3) = temp;
    cache.at(1) = moment;
    if (diff1<=diff2)
        return 1
    return -1


}


// Update map of bought symbols
void MainStrategy::calculate_signals(MarketEvent i_event) {
    
    // LONG any symbol whose bar is updated by marketevent
    for (int i=0; i < symbol_list->size(); i++) {
        string symbol = (*symbol_list)[i];
        map<string, map<long, double>> bars_50 = bars->get_latest_bars(symbol, 49);
        if (bars_50.empty()) continue;
        map<string, map<long, double>> bars_20 = bars->get_latest_bars(symbol, 19);
        if (bars_20.empty()) continue;

        double sma_50 = calculate_sma(bars_50["open"]);
        double sma_20 = calculate_sma(bars_20["open"]);

        if (sma_20 > sma_50 && !bought[symbol]) {
            events->push_back(new SignalEvent(symbol, bars_20["open"].rbegin()->first, 1.0));
            bought[symbol] = true;
        }
        else if (sma_50 > sma_20 && bought[symbol]) {
            events->push_back(new SignalEvent(symbol, bars_20["open"].rbegin()->first, -1.0));
            bought[symbol] = false;
        }
    }
}
