#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <map>

class Stock {
protected:
    std::string symbol;
    std::map<long, std::map<std::string, double>> data;
    long latestTimestamp;
public:
    Stock(std::string);
    ~Stock();

    std::string getSymbol();
    long getLatestTimestamp();
    std::map<long, std::map<std::string, double>> getData();
    virtual void updateData()=0;
};

class StockByDay: public Stock {
public:
    StockByDay(std::string);
    ~StockByDay();
    void updateData();
};

class StockByMinute: public Stock {
public:
    StockByMinute(std::string);
    ~StockByMinute();
    void updateData();
};

#endif // STOCK_H
