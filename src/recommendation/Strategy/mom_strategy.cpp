#include "mom_strategy.h"
#include "cmath"

MOMStrategy::MOMStrategy(Stock*& stock,bool& byMinute, std::string& priceType)
{

    this->stock = stock;
    this->byMinute = byMinute;
    this->priceType = priceType;

}

MOMStrategy::~MOMStrategy(){
    delete this->stock;
}



int MOMStrategy::auxiliary_momentum(std::map<int, double> &cache){
 //1-full, 0-sell, -1-perc
     if(cache.at(0)<1)
         return 0;
     double diff1=cache.at(3)-cache.at(2);
     double diff2=cache.at(1)-cache.at(0);

     if (diff1<=diff2)
         return 1;
     else {return -1;}
};



void MOMStrategy::update_numericSignals(long& depth){
    QVector<double> signalVector;
    int longTime = 9;
    int shortTime = 4;
    for (int startPeriod=0; startPeriod<depth; startPeriod++){
             std::map<long, double> bars_10 = this->get_data(longTime,startPeriod);
             std::map<long, double> bars_5 = this->get_data(shortTime,startPeriod);
             double sma_10 = this->calculate_sma(bars_10);
             double sma_5 = this->calculate_sma(bars_5);
             double moment = sma_5/sma_10;
             signalVector.push_front(moment);
            }
    this->numericSignals = signalVector;
};


double MOMStrategy::calculate_sma(std::map<long, double> &bars) {
         assert(!bars.empty());
         double sum = 0;
         for (auto &it : bars) {
             sum += it.second;
         }
         return sum / bars.size();
     };

std::tuple<bool, double> MOMStrategy::calculate_signal(){
     std::map<int, double> cache;
     int longTime = 9;
     int shortTime = 4;
     for (int k=0; k<4; k++){
         std::map<long, double> bars_10 = this->get_data(longTime,k);
         std::map<long, double> bars_5 = this->get_data(shortTime,k);
         double sma_10 = this->calculate_sma(bars_10);
         double sma_5 = this->calculate_sma(bars_5);
         double moment = sma_5/sma_10;
         cache.insert(std::pair<int, double>(k, moment));
     }

     int action = this->auxiliary_momentum(cache);
     if (action == 0){
         return std::tuple<bool,double>(false, 1.0);
     }
     else if (action == -1) {
         return std::tuple<bool,double>(true, 0.8);
     }
     if (action == 1){
         return std::tuple<bool,double>(true, 1.0);

}};
