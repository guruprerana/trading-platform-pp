#include "strategy.h"
#include "../components/stock/stock.h"
#include "../helper/QJsonObjectManipulation.h"
#include <string>
#include <tuple>


Strategy::Strategy(){
    data_by_minute = true;
    this->strategy_name = "None";
    this->stock = nullptr;
    this->data_by_minute = false; //by default it is by day 
    this->price_type = 'c'; // by default consider closing price 
}

Strategy::Strategy(char& strategy_name, Stock*& stock, bool data_by_minute, std::string price_type){
    this->strategy_name = strategy_name; //possible names {'MOM', 'EMA', 'LR'}
    this->stock = stock; 
    this->data_by_minute = data_by_minute; //if false, the data is provided by day
    this->price_type = price_type;
}

Strategy::~Strategy(){
    delete stock;
}



//Return only a map {time:price} for the last n days of starting from k days ago (k=0 for today, k=1 for yesterday...)
std::map<long, double> Startegy::get_data(int N, int k=0){
    if (this->data_by_minute){
        this->stock->updateDataByMinute();
        QJsonObject jsonData = this->stock->getDataByMinute();
    }
    else{
        this->stock->updateDataByDay();
        QJsonObject jsonData = this->stock->getDataByDay();
    }
    std::map<std::string, std::map<long, double>> mapData = convertToMap(jsonData); //converts the QJsonObject with the data of the last 6 months into a std::map<std::string, std::ap<long, double>> {price_type : {time:price}}
    for (auto it = mapData.begin(); it != mapData.end(); ++it){
        if (it->first == this.get_price_type()){ //take the map <long, double> associated to the price_type chosen at the beginning
            std::map<long, double> price_map = it->second;
        }
    }
    std::map<long, double> res;
    int count = 0;
    for (auto it = price_map.begin(); it != price_map.end(); ++it){
        if (count >=k && count <N+k){ 
            res[it->first] = it->second;
        }
        if count==N+k{
           return res;
        }
        count += 1;
    }
}

bool Strategy::exponential_moving_average(){

    std::map<long, double> bars_11 = this.get_data(11);
    if (bars_11.empty()) continue; // check if empty and include more bars
    std::map<long, double> bars_6 = this.get_data(6);
    if (bars_11.empty()) continue; // check if empty and include more bars
    double ema_11 = calculate_ema(bars_11); // Longer Moving Average
    double ema_06 = calculate_ema(bars_6);  // Shorter Moving Average
    double markup = 0.05;// markup introduces anticipation into our strategy:
    if (ema_06 > (1-markup)*ema_11 ) {
        return true;
    }
    else if (ema_11 > (1+markup)*ema_06 ) {
        return false;
    }
}


// Calculate Simple Moving Average 
double Strategy::calculate_sma(map<long, double> &bars) {
         assert(!bars.empty());
         double sum = 0;
         for (auto &it : bars) {
             sum += it.second;
         }
         return sum / bars.size();
     }


// Calculate Exponential Moving Average
double Strategy::calculate_ema(map<long, double> &bars) {
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


int Strategy::auxiliary_momentum(map<int, double> &cache, map<int, double> &cache_date, double moment, map<long, double> bars_5){
 //1-full, 0-sell, -1-perc
     if (cache.size()<3)
     {
         int k = cache.size();
         cache.insert(pair<int, double>(k+1, moment));
         cache_date.insert(pair<int, long>(k+1, bars_5.rbegin()->first));
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
     cache_date.insert(pair<int, long>(k+1, bars_5.rbegin()->first));
     if (diff1<=diff2)
         return 1;
     return -1;}
    
std::tuple<bool, double> Strategy::momentum(){
     map<int, double> cache;
     map<int, long> cache_date;
     map<long, double> bars_10 = this.get_data(9); // get the price of the N latest days for the stock 
     if (bars_10.empty()) continue;
     map<long, double> bars_5 = this.get_data(4);
     if (bars_5.empty()) continue;
     double sma_10 = calculate_sma(bars_10);
     double sma_5 = calculate_sma(bars_5);
     double moment = sma_5/sma_10;
     int action = auxiliary_momentum(cache, cache_date, moment,bars_5);
     if (action == 0 ){
         return true, 1.0;
     }
     else if (action == 1 ) {
         return true, 1.0;
     }
     else if (action == -1 ) {
         return true, 0.8;
     }      

}

double Strategy::compute_average_key(map<long, double> &bars){
    double key_average = 0;
    for (auto &item : bars) {
            key_average += item.first;
        }
    return (key_average/bars.size());
}

double Strategy::compute_average_value(map<long, double> &bars){
    double value_average = 0;
    for (auto &item : bars) {
            value_average += item.second;
        }
    return (value_average/bars.size());
}

double Strategy::auxiliary_linear_regression(map<long, double> &bars){
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
    return slope; 

}

bool Strategy::linear_regression(){
    map<long, double> bars = this.get_data(20);
    double slope = auxiliary_linear_regression(bars);
    if (slope <= 0){ 
        return false;
    }
    else{
        return true; 
    } 
}

std::tuple<bool, double> Strategy::calculate_signals(){
    bool bought;
    double percentage = 1.0;
    //provides outcome of the chosen strategy
    if (this.get_name() == 'EMA'){ //exponential moving average
        bought =  exponential_moving_average();
    }
    if (this.get_name() == 'MOM'){//momentum
        bought, percentage = momentum();
    }
    if (this.get_name() == 'LR'){//linear regression
        bought= linear_regression();
    } 
    return bought,percentage;
}

void Strategy::simulate(){
    //frederic will add it
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
std::string Strategy::get_price_type(){
    return  this->price_type;
}

