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


map<std::string, bool> Strategy::calculate_initial_bought() {
    //We initialize the map: all stocks are not bought yey
    bought = {};
    for (std::vector<int>::iterator i= this.stock.begin(); i!= this.stock.end(); i++){
        bought[(*i).getSymbol()] = false;
    }
    return bought;
}

//EACH TEAM NEEDS TO FILL ITS STRATEGY: the output is true if the stocks is bought, false otherwise and push back the event
bool Strategy::exponential_moving_average():
    //to be completed
    return true;

bool Strategy::momentum():
    //to be completed
    return true;

bool Strategy::linear_regression():
    //to be completed
    return true;


void Strategy::calculate_signals(){
    //provides outcome of the chosen strategy
    map<std::string, bool> bought_map = calculate_initial_bought();
    for (std::vector<int>::iterator i= this.stock.begin(); i!= this.stock.end(); i++){
        std::string symbol = (*i).getSymbol();
        bool bought;
        if (this.get_name() == 'EMA'){ //exponential moving average
        bought = exponential_moving_average();
        }
        if (this.get_name() == 'MOM'){//momentum
            bought = exponential_moving_average();
        }
        if (this.sget_name() == 'LR'){//linear regression
            bought = linear_regression();
        }
        if (bought){
            bought_map[symbol] = true;
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

