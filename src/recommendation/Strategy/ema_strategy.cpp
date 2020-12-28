#include "ema_strategy.h"

EMAStrategy::EMAStrategy(Stock*& stock,bool& byMinute, std::string& priceType)
{

    this->stock = stock;
    this->byMinute = byMinute;
    this->priceType = priceType;
    signalReferences.push_back(1-markups.first);
    signalReferences.push_back(1-markups.second);
}

EMAStrategy::~EMAStrategy(){
    delete this->stock;
}

std::pair<double,double> EMAStrategy::get_markups(){
    return this->markups ;
}

void EMAStrategy::set_markups(std::pair<double,double>& markups){
    this->markups = markups;
}

double EMAStrategy::firstAuxillary(std::map<long, double> &bars){

    assert(!bars.empty());
    double e_MovingAverage = 0;
    double smoothing_parameter = 0.4;
    int weight_factor = 0;
    for (auto &it : bars) {
        e_MovingAverage += smoothing_parameter * (std::pow((1-smoothing_parameter),weight_factor)) * it.second;
        weight_factor += 1;
    }
    return e_MovingAverage;

};

void EMAStrategy::update_numericSignals(long& depth){
    QVector<double> signalVector;
    int startPeriod = 0;
    int longTime = 11;
    int shortTime = 6;
    for (long i=0; i<depth; i++){
        if (i<depth-11){
        std::map<long, double> bars_11 = this->get_data(longTime,startPeriod);
        std::map<long, double> bars_6 = this->get_data(shortTime,startPeriod);
        double ema_11 = this->firstAuxillary(bars_11);
        double ema_06 = this->firstAuxillary(bars_6);
        signalVector.push_front(ema_06/ema_11);
        startPeriod += 1;

        }
        else{
        signalVector.push_front(signalVector.front());
        }
    }
    this->numericSignals = signalVector;
};

std::tuple<bool, double> EMAStrategy::calculate_signal(){
    int longPeriod = 11;
    int shortPeriod = 6;
    int startPeriod = 0;
    std::map<long, double> bars_11 = this->get_data(longPeriod,startPeriod);
    std::map<long, double> bars_6 = this->get_data(shortPeriod,startPeriod);
    double ema_11 = this->firstAuxillary(bars_11);
    double ema_06 = this->firstAuxillary(bars_6);
    if (ema_06/ema_11 > (signalReferences[0])) {
        return std::tuple<bool,double>(true,1.0);
    }
    else if (ema_06/ema_11 < signalReferences[1]){
        return std::tuple<bool,double>(false,1.0);
    }
    else{
        return std::tuple<bool,double>(true,0.0);
    }
}

