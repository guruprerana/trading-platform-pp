#include "strategiesheader.hpp"

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

// Calculate Simple Moving Average 
double calculate_sma(map<long, double> &bars) {
    assert(!bars.empty());
    double sum = 0;
    for (auto &it : bars) {
        sum += it.second;
    }
    return sum / bars.size();
}





map<int, double> cache;



int momentum(map<int, double> &cache, double moment){
//1-full, 0-sell, -1-perc
    if (cache.size()<3)
    {
    	int k = cache.size();
        cache.insert(pair<int, double>(k+1, moment));
        if (moment>=1)
            return 1;
        return 0;

    }
  

    if(moment<1)
        return 0;
	
    double diff1=cache.at(3)-cache.at(2);
    double diff2=cache.at(1)-moment;
    double temp= cache.at(2);
    cache.at(2) = cache.at(1);
    cache.at(3) = temp;
    cache.at(1) = moment;
    if (diff1<=diff2)
        return 1;
    return -1;


}






// Update map of bought symbols
void MainStrategy::calculate_signals(MarketEvent i_event) {

    
            
    // LONG any symbol whose bar is updated by marketevent
    for (int i=0; i < symbol_list->size(); i++) {
        string symbol = (*symbol_list)[i];
        map<string, map<long, double>> bars_10 = bars->get_latest_bars(symbol, 9);
        if (bars_10.empty()) continue;
        map<string, map<long, double>> bars_5 = bars->get_latest_bars(symbol, 4);
        if (bars_5.empty()) continue;

        double sma_10 = calculate_sma(bars_10["open"]);
        double sma_5 = calculate_sma(bars_5["open"]);
        double moment = sma_5/sma_10;
        int action = momentum(cache, moment);
        if (action == 0 && bought[symbol]){
            events->push_back(new SignalEvent(symbol, bars_5["open"].rbegin()->first, -1.0));
            bought[symbol] = false;
        }
        else if (action == 1 && !bought[symbol]) {
            events->push_back(new SignalEvent(symbol, bars_5["open"].rbegin()->first, 1.0));
            bought[symbol] = true;
        }
        else if (action == -1 && !bought[symbol]) {
            events->push_back(new SignalEvent(symbol, bars_5["open"].rbegin()->first, 0.8));
            bought[symbol] = true;
        }
        
 
    }
}
