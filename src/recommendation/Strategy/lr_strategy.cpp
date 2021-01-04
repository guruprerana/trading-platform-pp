#include "lr_strategy.h"
#include "cmath"

LRStrategy::LRStrategy(Stock*& stock,bool& byMinute, std::string& priceType)
{
    this->stock = stock;
    this->byMinute = byMinute;
    this->priceType = priceType;
}

LRStrategy::~LRStrategy(){
    delete this->stock;
}


void LRStrategy::update_numericSignals(long& depth){
    QVector<double> signalVector;
    int longTime = 11;
    int shortTime = 6;
    std::map<long, double> bars = this->get_data(20);
    auto res = this->auxiliary_linear_regression(bars);
    double slope = std::get<0>(res);
    double yintercept = std::get<1>(res);
    for (int startPeriod=0; startPeriod<depth; startPeriod++){
    double image = slope*(startPeriod)+yintercept;
    signalVector.push_front(image);

}
    this->numericSignals = signalVector;}

double LRStrategy::compute_average_key(std::map<long, double> &bars){
    double key_average = 0;
    for (auto &item : bars) {
            key_average += item.first;
        }
    return (key_average/bars.size());
}

double LRStrategy::compute_average_value(std::map<long, double> &bars){
    double value_average = 0;
    for (auto &item : bars) {
            value_average += item.second;
        }
    return (value_average/bars.size());
}

std::tuple<bool, double> LRStrategy::calculate_signal(){
    std::map<long, double> bars = this->get_data(20);
    auto res = this->auxiliary_linear_regression(bars);
    double slope = std::get<0>(res);
    if (slope <= 0){
        return std::tuple<bool,double>(false, 1.0);
    }
    else{
        return std::tuple<bool,double>(true, 1.0);
    }
}

std::tuple<bool, double> LRStrategy::auxiliary_linear_regression(std::map<long, double> &bars){
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
    return std::tuple<bool,double>(slope, intercept); //use the slope and the y-intercept in the plot of simulate

}
