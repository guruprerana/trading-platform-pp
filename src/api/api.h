#ifndef API_H
#define API_H

#include <curl/curl.h>
#include <map>
#include <string>
//#include <nlohmann/json.hpp>
// using json = nlohmann::json;

class API {
public:
  API();
  ~API();

  std::string API_ENDPOINT = "https://finnhub.io/api/v1/stock/candle?symbol=";
  std::string API_TOKEN = "buk0iff48v6r2017bpg0";

  std::string getStockData(std::string stockSymbol, std::string resolution,
                           long startTimestamp, long endTimestamp);

private:
  // CURL object here
  CURL *curl;
  CURLcode result;
  struct curl_slist *headers = NULL;
};

#endif // API_H
