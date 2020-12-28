#include "strategy.h"
#include "../../../src/helper/helper.h"
#include <string>
#include <tuple>
#include <map>
#include <cmath>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

using namespace helper;
Strategy::Strategy()
{

    this->strategyName = "None";
    this->stock = nullptr;
    this->byMinute = false;
    this->priceType = "c";
}

Strategy::Strategy(std::string& strategyName, Stock*& stock, bool& byMinute, std::string& priceType){
    this->strategyName = strategyName;
    this->stock = stock;
    this->byMinute = byMinute; //if false, the data is provided by day
    this->priceType = priceType;
}

Strategy::~Strategy(){
    delete stock;
}

Stock* Strategy::get_stock(){
    return this->stock;
}

std::string Strategy::get_priceType(){
    return this->priceType;
}

bool Strategy::get_byMinute(){
    return this->byMinute;
}

void Strategy::set_stock(Stock*& other_stock){
   this->stock =  other_stock;
}

void Strategy::set_priceType(std::string& other_priceType){
    this->priceType = other_priceType;
}

void Strategy::set_byMinute(bool& other_byMinute){
    this->byMinute = other_byMinute;
}

std::map<long, double> Strategy::get_data(int& nLatestPeriods, int& startingPeriod){
    QJsonObject jsonData;
    if (this->byMinute){
        jsonData = this->stock->getDataByMinute();
    }
    else{
        jsonData = this->stock->getDataByDay();
    }
    std::map<std::string, std::map<long, double>> mapData = convertToMap(jsonData);
    std::map<long, double> price_map;
    for (auto it = mapData.begin(); it != mapData.end(); ++it){
        if(it->first == this->get_priceType()){
            std::map<long, double> price_map = it->second;
        }
    }
    std::map<long, double> res;
    std::map<long,double>::reverse_iterator it = price_map.rbegin()+startingPeriod;
    while (it != price_map.rbegin()+startingPeriod+nLatestPeriods){
        res[it->first] = it->second;
    }
    return res;
}

void Strategy::evaluate(){
}

void Strategy::compare(Strategy*& other_strategy){
other_strategy = new Strategy();
}

