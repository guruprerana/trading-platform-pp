#include "stock.h"
#include "api/api.h"

#include <iostream>
Stock::Stock(std::string symbol){
    this->symbol = symbol;
}

Stock::~Stock(){

}

std::string Stock::getSymbol(){
    return symbol;
}

long Stock::getLatestTimestamp(){
    return latestTimestamp;
}

std::map<long, std::map<std::string, double>> Stock::getData(){
    return data;
}

StockByDay::StockByDay(std::string symbol): Stock(symbol){

}

StockByDay::~StockByDay(){

}

void StockByDay::updateData(){

}

StockByMinute::StockByMinute(std::string symbol): Stock(symbol){

}

StockByMinute::~StockByMinute(){

}

void StockByMinute::updateData(){

}








