#ifndef API_H
#define API_H

#include <map>
#include <string>
#include <curl/curl.h>
//#include <nlohmann/json.hpp>
//using json = nlohmann::json;
class API {
public:
    API();
    ~API();
    void url_set(std::string stockSymbol,std::string resolution, long startTimestamp, long endTimestamp) ;// Contains the url + parameters
    std::string getStockData(std::string stockSymbol,std::string resolution, long startTimestamp, long endTimestamp);
    std::string get(){ return url_used;};
private:
    // CURL object here
    CURL *curl ;
    CURLcode result;
    struct curl_slist *headers= NULL;
    std::string token = "buk0iff48v6r2017bpg0"; // The API token which will be used
    std::string data; //Contains the data
    std::string url="https://finnhub.io/api/v1/stock/candle?symbol=";
    std::string url_used;
};
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s); // Writing function for curl request

#endif // API_H
