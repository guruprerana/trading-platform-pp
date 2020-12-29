#include "stock.h"
#include "api/api.h"
#include "helper/helper.h"
#include <ctime>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <string>

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

QMap<std::string, QVector<double>> Stock::getDataByMinute() {
  return dataByMinute;
}

std::string Stock::getNews() {
  return stockNews;
}


QMap<std::string, QVector<double>> Stock::updateDataByMinute() {
  API *api = new API();
  std::time_t t = std::time(0);
  std::string apiResponse = api->getStockData(getSymbol(), "1",
                            std::max(t - 459200, getLatestTimestampByMinute()), t);
  // 259200 represents 3 days in seconds. Basically we want the api to call 3 days worth of data with 1-minute intervals
  // if we have never called the data before otherwise we update.
  latestTimeStampByMinute = t;
  QMap<std::string, QVector<double>> updateMap;

  //update latestTimeStampByMinute
  if (apiResponse != "{\"s\":\"no_data\"}") {
    QJsonObject dataUpdate = helper::parseJson(apiResponse);
    std::string s = "chlot";

    for (char &c : s) {
      std::string k(1, c);
      QVector<double> initialVector = dataByMinute[k];
      QVector<double> vectorToAppend = helper::convert_to_vector(dataUpdate, k);
      initialVector += vectorToAppend;
      dataByMinute[k] = initialVector;
      updateMap[k] = vectorToAppend;
    }
  }

  return updateMap;
}

void Stock::updateDataByDay() {
  API *api = new API();
  std::time_t t = std::time(0);
  std::string apiResponse = api->getStockData(getSymbol(), "D",
                            std::max(t - 15768000, getLatestTimestampByDay()), t);
  // 15768000 represents 6 months in seconds. Basically we want the api to call 6 months worth of data with 1-day intervals
  // if we have never called the data before, otherwise we only update what we are missing
  latestTimeStampByDay = t;

  //update latestTimeStampByDay
  if (apiResponse != "{\"s\":\"no_data\"}") {
    dataByDay = helper::parseJson(apiResponse);
  }
}

void Stock::updateNews() {
  API *api = new API();
  std::time_t t = std::time(0);
  std::string apiResponse = api->getNewsCompany(getSymbol(),
                            helper::convertToReadable(t),
                            helper::convertToReadable(t));
  //We do not change convertToReadable(t) because it gives the current date and the api gives news with day intervals.
  // Basically, we want all the news today regardless of the exact time.
  stockNews = apiResponse;
}
















