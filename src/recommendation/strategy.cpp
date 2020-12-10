#include "strategy.h"
#include "stock.h"
#include "api.h"
#include <vector>
#include <string>


Strategy::Strategy(){
    data_by_minute = True;
    this->strategy_name = "None";
    this->stock = std::vector<Stock*>; // vector of objects Stock
    this->data_by_minute = false; //by default it is by day ?
    this->price_type = 'c'; // by default consider closing price ?
}

Strategy::Strategy(char& strategy_name, std::vector<Stock*> stocks_vector, bool data_by_minute, std::string price_type){
    this->strategy_name = strategy_name; //possible names {'MOM', 'EMA', 'LR'}
    this->stock = stocks_vector; //needs to be not empty
    this->data_by_minute = data_by_minute; //if false, the data is provided by day
    this->price_type = price_type;
}

Strategy::~Strategy(){
    delete stock;
}



//EACH TEAM NEEDS TO FILL ITS STRATEGY: the output is true if the stocks is bought, false otherwise and push back the event
bool Strategy::exponential_moving_average(symbol):{
    
    map<string, map<long, double>> bars_11 = bars->get_latest_bars(symbol,11);
    if (bars_11.empty()) continue; // check if empty and include more bars
    map<string, map<long, double>> bars_6 = bars->get_latest_bars(symbol,6);
    if (bars_11.empty()) continue; // check if empty and include more bars
    double ema_11 = calculate_ema(bars_11["open"]); // Longer Moving Average
    double ema_06 = calculate_ema(bars_6["open"]);  // Shorter Moving Average
    double markup = 0.05;// markup introduces anticipation into our strategy:
    if (ema_06 > (1-markup)*ema_11 && !bought[symbol]) {
        return true;
    }
    else if (ema_11 > (1+markup)*ema_06 && bought[symbol]) {
        return false;
    }
    }



bool Strategy::momentum(symbol):{
    
    map<int, double> cache;
    map<int, long> cache_date;
    map<string, map<long, double>> bars_10 = bars->get_latest_bars(symbol, 9); // get the price of the _ latest days for the stock "symbol"
    if (bars_10.empty()) continue;
    map<string, map<long, double>> bars_5 = bars->get_latest_bars(symbol, 4);
    if (bars_5.empty()) continue;
    double sma_10 = calculate_sma(bars_10["open"]);
    double sma_5 = calculate_sma(bars_5["open"]);
    double moment = sma_5/sma_10;
    int action = momentum(cache, cache_date, moment,bars_5);
    if (action == 0 && bought[symbol]){
        return true, 1.0;
    }
    else if (action == 1 && !bought[symbol]) {
        return true, 1.0;
    }
    else if (action == -1 && !bought[symbol]) {
        return true, 0.8;
    }      

        }
    

    

bool Strategy::linear_regression(symbol):
    //to be completed
    return true;


void Strategy::calculate_signals(symbol){
    //provides outcome of the chosen strategy
        bool bought;
        double percentage;
        percentage = 1.0;
        if (this.get_name() == 'EMA'){ //exponential moving average
        bought = exponential_moving_average(symbol);
        }
        if (this.get_name() == 'MOM'){//momentum
            bought = exponential_moving_average(symbol);
        }
        if (this.sget_name() == 'LR'){//linear regression
            bought, percentage = linear_regression(symbol);
        }
        

    }
   
}

void Strategy::simulate(){
    if (this->data_by_minute){
        this->stock->updateDataByMinute();
        QJsonObject data = this->stock->getDataByMinute();
    }
    else{
        this->stock->updateDataByDay();
        QJsonObject data = this->stock->getDataByDay();
    }
    QVariantMap dataMap = data.toVariantMap(); // easier to work with a map
    if (!dataMap.isEmpty()){
        QString Qprice_type = QString::fromStdString(this.price_type); 
        QVariantMap::const_iterator pos = dataMap.find(Qprice_type);//iterator pointing to the item with key 'price type' in the map.
        if (pos != end()){// if map contains item with key Qpricetype
            QVariantList price_stream = pos->value<QVariantList>();
            QLineSeries* StockTimeSeries = new QLineSeries();
            for(double k=0; k<price_stream.size();k++){
                double k_term = price_stream[k].toDouble();
                StockTimeSeries->append(k,k_term) ;

            }
        QChart *StockChart = new QChart();
        StockChart->addSeries(StockTimeSeries);
        QChartView StockChartView(StockChart);
        }
    }
}

void Strategy::evaluate(){

}
void Strategy::compare(Strategy* other_strategy){

}

void Strategy::set_stock(Stock* stock){
    this->stock = stock;
}
std::vector<Stock*> Strategy::get_stock(){
    return this->stock;

}
std::string Strategy::get_name(){
    return  this->strategy_name;
}

// auxiliary functions needed for the strategies 
int momentum(map<int, double> &cache, map<int, double> &cache_date, double moment, map<string, map<long, double>> bars_5){
//1-full, 0-sell, -1-perc
    if (cache.size()<3)
    {
        int k = cache.size();
        cache.insert(pair<int, double>(k+1, moment));
        cache_date.insert(pair<int, long>(k+1, bars_5["open"].rbegin()->first));
        if (moment>=1)
            return 1;
        return 0;

    }
  

    if(moment<1)
        return 0;

    int k = cache.size();
    double diff1=cache.at(k-2)-cache.at(k-1);
    double diff2=cache.at(k)-moment;

    cache.insert(pair<int, double>(k+1, moment));
    cache_date.insert(pair<int, long>(k+1, bars_5["open"].rbegin()->first));
    if (diff1<=diff2)
        return 1;
    return -1;}


    // Calculate Simple Moving Average 
    double calculate_sma(map<long, double> &bars) {
        assert(!bars.empty());
        double sum = 0;
        for (auto &it : bars) {
            sum += it.second;
        }
        return sum / bars.size();
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
    

