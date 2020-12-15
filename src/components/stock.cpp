#include "stock.h"
#include "../api/api.h"
#include "../helper/QJsonObjectManipulation.h"
#include <ctime>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

Stock::Stock(std::string symbol) {
  this->symbol = symbol;
  latestTimeStampByDay = 0;
  latestTimeStampByMinute = 0;
  stockNews = "";
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

std::string Stock::getNews() {
  return stockNews;
}


void Stock::updateDataByMinute() {
  API *api = new API();
  std::time_t t = std::time(0);
  std::string apiResponse = api->getStockData(getSymbol(), "1",
                            t - 259200, t);
  // 259200 represents 3 days in seconds. Basically we want the api to call 3 days worth of data with 1-minute intervals
  latestTimeStampByMinute = t;

  //update latestTimeStampByMinute
  if (apiResponse != "{\"s\":\"no_data\"}") {
    dataByMinute = parseJson(apiResponse);
  }
}

void Stock::updateDataByDay() {
  API *api = new API();
  std::time_t t = std::time(0);
  std::string apiResponse = api->getStockData(getSymbol(), "D",
                            t - 15768000, t);
  // 15768000 represents 6 months in seconds. Basically we want the api to call 6 months worth of data with 1-day intervals
  latestTimeStampByDay = t;

  //update latestTimeStampByDay
  if (apiResponse != "{\"s\":\"no_data\"}") {
    dataByDay = parseJson(apiResponse);
  }
}

void Stock::updateNews() {
  API *api = new API();
  std::time_t t = std::time(0);
  std::string apiResponse = api->getNews(getSymbol(),
                                         convertToReadable(t - 7200),
                                         convertToReadable(t));
  //7200 represents 2 hours in seconds. Market news up to 2 hours are necessary for trading.
  stockNews = apiResponse;
}
















