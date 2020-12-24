#ifndef API_H
#define API_H

#include <curl/curl.h>
#include <map>
#include <string>

class API {
 public:
  API();
  ~API();

  std::string API_ENDPOINT = "https://finnhub.io/api/v1/stock/candle?symbol=";
  std::string API_NEWSCOMPANY = "https://finnhub.io/api/v1/company-news?symbol=";
  std::string API_NEWSMARKET =
    "https://finnhub.io/api/v1/news?category=general&token=";
  std::string API_TOKEN = "buk0iff48v6r2017bpg0";
  std::string callUrl(std::string url);
  std::string getStockData(std::string stockSymbol, std::string resolution,
                           long startTimestamp, long endTimestamp);
  std::string getNewsCompany(std::string stockSymbol, std::string startTimestamp,
                             std::string endTimestamp);

  std::string getNewsMarket();

 private:
  // CURL object here
  CURL *curl;
  CURLcode result;
  struct curl_slist *headers = NULL;
};

#endif // API_H
