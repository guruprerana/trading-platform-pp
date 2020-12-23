#ifndef API_H
#define API_H

#include <curl/curl.h>
#include <map>
#include <string>
#include <QObject>

class API {
 public:
  API();
  ~API();

  static const std::string
  API_ENDPOINT,
  API_NEWSCOMPANY,
  API_NEWSMARKET,
  API_TOKEN;

  std::string callUrl(std::string url);
  std::string getStockData(std::string stockSymbol, std::string resolution,
                           qint64 startTimestamp, qint64 endTimestamp);
  std::string getNewsCompany(std::string stockSymbol,
                             std::string startTimestamp,
                             std::string endTimestamp);
  std::string getNewsMarket();

 private:
  Q_GADGET

  // CURL object here
  CURL *curl;
  CURLcode result;
  struct curl_slist *headers = NULL;

};

#endif // API_H
