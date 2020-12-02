#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <QJsonObject>

class Stock {
 private:
  std::string symbol;
  QJsonObject dataByDay;
  QJsonObject dataByMinute;
  long latestTimeStampByDay;
  long latestTimeStampByMinute;

 public:
  Stock(std::string);
  ~Stock();

  QJsonObject parseJson(std::string);
  std::string getSymbol();
  long getLatestTimestampByDay();
  long getLatestTimestampByMinute();
  QJsonObject getDataByDay();
  QJsonObject getDataByMinute();
  void updateDataByDay();
  void updateDataByMinute();
};

#endif // STOCK_H
