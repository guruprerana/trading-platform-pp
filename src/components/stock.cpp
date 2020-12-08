#include "stock.h"
#include "../api/api.h"
#include "../helper/QJsonObjectManipulation.h"
#include <ctime>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
#include <QVector>
Stock::Stock(std::string symbol) {
    this->symbol = symbol;
    latestTimeStampByDay = 0;
    latestTimeStampByMinute = 0;
}
//latestTimeStamp = 0 is an initializtion that represents that all our data will be taken after 00:00, Jan 1, 1970, UTC.


Stock::~Stock() {

}

std::string Stock::getSymbol() {
    return symbol;
}

long Stock::getLatestTimestampByDay() {
    return latestTimeStampByDay;
}

long Stock::getLatestTimestampByMinute() {
    return latestTimeStampByMinute;
}

QJsonObject Stock::getDataByDay() {
    return dataByDay;
}

QJsonObject Stock::getDataByMinute() {
    return dataByMinute;
}

void Stock::updateDataByMinute(){
    API *api = new API();
    std::time_t t = std::time(0);
    std::string apiResponse = api->getStockData(getSymbol(), "1", std::max(t-604800,latestTimeStampByMinute), t);
    // 604800 represents one week in seconds. Basically we want the api to call one week worth of data with 1-minute intervals
    latestTimeStampByMinute = t;
    //update latestTimeStampByMinute
    if (apiResponse != "{\"s\":\"no_data\"}"){
        dataByMinute = parseJson(apiResponse);
    }
}

void Stock::updateDataByDay(){
    API *api = new API();
    std::time_t t = std::time(0);
    std::string apiResponse = api->getStockData(getSymbol(), "D", std::max(t-31536000,latestTimeStampByDay), t);
    // 31536000 represents one year in seconds. Basically we want the api to call one year worth of data with 1-day intervals
    latestTimeStampByDay = t;
    //update latestTimeStampByDay
    if (apiResponse != "{\"s\":\"no_data\"}"){
        dataByDay = parseJson(apiResponse);
    }
}
QVector<double> convert_to_vector(QJsonObject j,std::string k){
    QVariantMap j_map=j.toVariantMap();
    QVariantList j_list =j_map[k.c_str()].toList();
    QVector<double> q;
    for (int i=0;i<j_list.count();i++)
    {
        q.append(j_list[i].toDouble());
    }
    return q;
}
















