#include "strategy.h"
#include "../components/stock.h"
#include "../helper/helper.cpp"
#include "../helper/helper.h"
#include <string>
#include <tuple>
#include <map>
#include <cmath>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

using std::string;
using std::map;

Strategy::Strategy(){
    data_by_minute = true;
    this->strategy_name = "None";
    this->stock = nullptr;
    this->data_by_minute = false; //by default it is by day
    this->price_type = 'c'; // by default consider closing price
}

Strategy::Strategy(std::string strategy_name, Stock *stock, bool data_by_minute, std::string price_type){
    this->strategy_name = strategy_name; //possible names {'MOM', 'EMA', 'LR'}
    this->stock = stock;
    this->data_by_minute = data_by_minute; //if false, the data is provided by day
    this->price_type = price_type;

}

Strategy::~Strategy(){
    delete stock;
}



//Return only a map {time:price} for the last n days of starting from k days ago (k=0 for today, k=1 for yesterday...)
std::map<long, double> Strategy::get_data(int N, int k){
    QJsonObject jsonData;
    if (this->data_by_minute){
        this->stock->updateDataByMinute();
        jsonData = this->stock->getDataByMinute();
    }
    else{
        this->stock->updateDataByDay();
        jsonData = this->stock->getDataByDay();
    }
    std::map<std::string, std::map<long, double>> mapData = helper::convertToMap(jsonData); //converts the QJsonObject with the data of the last 6 months into a std::map<std::string, std::ap<long, double>> {price_type : {time:price}}
    std::map<long, double> price_map;
    for (auto it = mapData.begin(); it != mapData.end(); ++it){
        if (it->first == this->get_price_type()){ //take the map <long, double> associated to the price_type chosen at the beginning
            std::map<long, double> price_map = it->second;
        }
    }
    std::map<long, double> res;
    int count = 0;
    for (auto it = price_map.begin(); it != price_map.end(); ++it){
        if (count >=k && count <N+k){
            res[it->first] = it->second;
        }
        if (count==N+k){
           return res;
        }
        count += 1;
    }
}

bool Strategy::exponential_moving_average(){

    std::map<long, double> bars_11 = this->get_data(11);
    std::map<long, double> bars_6 = this->get_data(6);
    double ema_11 = this->calculate_ema(bars_11); // Longer Moving Average
    double ema_06 = this->calculate_ema(bars_6);  // Shorter Moving Average
    double markup = 0.05;// markup introduces anticipation into our strategy:
    if (ema_06 > (1-markup)*ema_11 ) {
        return true;
    }
    else if (ema_11 > (1+markup)*ema_06 ) {
        return false;
    }
}


// Calculate Simple Moving Average
double Strategy::calculate_sma(std::map<long, double> &bars) {
         assert(!bars.empty());
         double sum = 0;
         for (auto &it : bars) {
             sum += it.second;
         }
         return sum / bars.size();
     }


// Calculate Exponential Moving Average
double Strategy::calculate_ema(std::map<long, double> &bars) {
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


int Strategy::auxiliary_momentum(std::map<int, double> &cache){
 //1-full, 0-sell, -1-perc
     if(cache.at(0)<1)
         return 0;
     double diff1=cache.at(3)-cache.at(2);
     double diff2=cache.at(1)-cache.at(0);

     if (diff1<=diff2)
         return 1;
     else {return -1;}}
    
std::tuple<bool, double> Strategy::momentum(){
     std::map<int, double> cache;
     for (int k=0; k<4; k++){
         std::map<long, double> bars_10 = this->get_data(9,k);
         std::map<long, double> bars_5 = this->get_data(4,k);
         double sma_10 = this->calculate_sma(bars_10);
         double sma_5 = this->calculate_sma(bars_5);
         double moment = sma_5/sma_10;
         cache.insert(std::pair<int, double>(k, moment));
     }

     int action = this->auxiliary_momentum(cache);
     if (action == 0){
         return std::make_tuple(false, 1.0);
     }
     else if (action == -1) {
         return std::make_tuple(true, 0.8);
     }
     if (action == 1){
         return std::make_tuple(true, 1.0);

}}

double Strategy::compute_average_key(std::map<long, double> &bars){
    double key_average = 0;
    for (auto &item : bars) {
            key_average += item.first;
        }
    return (key_average/bars.size());
}

double Strategy::compute_average_value(std::map<long, double> &bars){
    double value_average = 0;
    for (auto &item : bars) {
            value_average += item.second;
        }
    return (value_average/bars.size());
}

std::tuple<bool, double> Strategy::auxiliary_linear_regression(std::map<long, double> &bars){
    assert(!bars.empty());
    double value_average= this->compute_average_value(bars);
    double key_average= this->compute_average_key(bars);
    double ss_xy = 0;
    double ss_xx = 0;
    for (auto &item : bars) {
            ss_xx += (item.first- key_average)* (item.second - value_average);
            ss_xy += pow(item.first- key_average, 2);
        }
    double slope = ss_xx/ss_xy;
    double intercept = value_average -slope* key_average;
    return std::make_tuple(slope, intercept); //use the slope and the y-intercept in the plot of simulate

}

bool Strategy::linear_regression(){
    std::map<long, double> bars = this->get_data(20);
    auto res = this->auxiliary_linear_regression(bars);
    double slope = std::get<0>(res);
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
    std::string name = this->get_name();
    if (this->str1.compare(name) == 0){ //exponential moving average
        bought =  this->exponential_moving_average();
     }
    if (this->str2.compare(name) == 0){
        auto res = this->momentum();
        bought = std::get<0>(res);
        percentage = std::get<1>(res);
    }
    if (this->str3.compare(name) == 0){//linear regression
        bought= this->linear_regression();
    }
    return std::make_tuple(bought, percentage);
}

void Strategy::simulate(){
    
     std::map<int, double> data_plot_short; // map (day --> momentum/ short_ema/ linear regression  ) where day = 1 is yesterday,
    // day = 2 is the day before, ...
     std::map<int, double> data_plot_long; // map (day --> long_ema) where day = 1 is yesterday,
    // day = 2 is the day before, ...
    int nb_points = 7; // number of points in our plot (ex : plot of the momentum of the 7 latest days)
    std::string name = this->get_name();

    if (this->str1.compare(name) == 0){ //exponential moving average
        for (int k=0; k<nb_points; k++){
        std::map<long, double> bars_11 = this->get_data(11);
        std::map<long, double> bars_6 = this->get_data(6);
        double ema_11 = this->calculate_ema(bars_11); // Longer Moving Average
        double ema_06 = this->calculate_ema(bars_6);
        data_plot_short.insert(std::pair<int, double>(k, ema_06));
        data_plot_long.insert(std::pair<int, double>(k, ema_11));
        }
    }
    
    
    if (this->str2.compare(name) == 0){//momentum
        for (int k=0; k<nb_points; k++){
         std::map<long, double> bars_10 = this->get_data(9,k);
         std::map<long, double> bars_5 = this->get_data(4,k);
         double sma_10 = this->calculate_sma(bars_10);
         double sma_5 = this->calculate_sma(bars_5);
         double moment = sma_5/sma_10;
         data_plot_short.insert(std::pair<int, double>(k, moment));
        }
    }
    
    
    
    if (this->str3.compare(name) == 0){//linear regression
        std::map<long, double> bars = this->get_data(20);
        auto res = this->auxiliary_linear_regression(bars);
        double slope = std::get<0>(res);
        double yintercept = std::get<1>(res);
        for (int k=0; k<nb_points; k++){
        double image = slope*(-k)+yintercept;
        data_plot_short.insert(std::pair<int, double>(k, image));
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
Stock* Strategy::get_stock(){
    return this->stock;

}
std::string Strategy::get_name(){
    return  this->strategy_name;
}
std::string Strategy::get_price_type(){
    return  this->price_type;
}

