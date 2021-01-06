#include "stock.h"
#include "api/api.h"
#include "helper/helper.h"
#include <ctime>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <string>

Stock::Stock(std::string symbol): symbol(symbol) {
  latestTimeStampByDay = 0;
  latestTimeStampByMinute = 0;
  stockNews = QJsonArray();
  api = new API();
}
//latestTimeStamp = 0 is an initializtion that represents that all our data will be taken after 00:00, Jan 1, 1970, UTC.


Stock::~Stock() {
  delete api;
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

int Stock::getDataByMinuteSize() {
  return dataByMinute["h"].size();
}

QMap<std::string, double> Stock::getDataByMinute(int idx) {
  QMap<std::string, double> ret;
  std::string s = "chlot";

  for (char &c : s) {
    std::string k(1, c);
    ret[k] = dataByMinute[k][idx];
  }

  return ret;
}

QJsonArray Stock::getNews() {
  return stockNews;
}

QJsonObject Stock::getSentimentData() {
  return sentimentData;
}


void Stock::updateDataByMinute() {
  std::time_t t = std::time(0);

  if (t - latestTimeStampByMinute < 60) {
    return;
  }

  std::string apiResponse = api->getStockData(getSymbol(), "1",
                            std::max(t - 259200, getLatestTimestampByMinute() - 1000), t);

  // 259200 represents 3 days in seconds. Basically we want the api to call 3 days worth of data with 1-minute intervals
  // if we have never called the data before otherwise we update.

  //update latestTimeStampByMinute
  if (apiResponse != "{\"s\":\"no_data\"}") {
    QJsonObject dataUpdate = helper::parseJson(apiResponse);

    auto t = helper::convert_to_vector(dataUpdate, "t");
    auto o = helper::convert_to_vector(dataUpdate, "o");
    auto h = helper::convert_to_vector(dataUpdate, "h");
    auto l = helper::convert_to_vector(dataUpdate, "l");
    auto c = helper::convert_to_vector(dataUpdate, "c");

    for (int i = 0; i < t.size(); ++i) {
      if (dataByMinute["t"].isEmpty() || t[i] >= dataByMinute["t"].back()) {
        dataByMinute["t"].append(t[i]);
        dataByMinute["o"].append(o[i]);
        dataByMinute["h"].append(h[i]);
        dataByMinute["l"].append(l[i]);
        dataByMinute["c"].append(c[i]);
      }
    }
  }

  latestTimeStampByMinute = t;
}

void Stock::updateDataByDay() {
  if (getLatestTimestampByDay() > 0) { // only update data by day once
    return;
  }

  std::time_t t = std::time(0);
  std::string apiResponse = api->getStockData(getSymbol(), "D", t - 15768000, t);
  // 15768000 represents 6 months in seconds. Basically we want the api to call 6 months worth of data with 1-day intervals
  latestTimeStampByDay = t;

  //update latestTimeStampByDay
  if (apiResponse != "{\"s\":\"no_data\"}") {
    dataByDay = helper::parseJson(apiResponse);
  }
}

void Stock::updateNews() {
  std::time_t t = std::time(0);
  std::string apiResponse = api->getNewsCompany(getSymbol(),
                            helper::convertToReadable(t),
                            helper::convertToReadable(t));
  // We do not change convertToReadable(t) because it gives the current date and the api gives news with day intervals.
  // Basically, we want all the news today regardless of the exact time.
  stockNews = helper::convertStringToQJsonArray(apiResponse);
}

void Stock::updateSentimentData() {
  std::string apiResponse = api->getSentimentData(getSymbol());
  sentimentData = helper::parseJson(apiResponse);
}















