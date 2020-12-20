#include "api.h"

// Constructor of the API class
API::API() {
  // Initiate the CURL object
  curl_global_init(CURL_GLOBAL_DEFAULT);
}

API::~API() {
  curl = NULL;
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append(static_cast<char *>(ptr), size * nmemb);
  return size * nmemb;
}

// Gets the stock data from the API
std::string API::getStockData(std::string stockSymbol, std::string resolution,
                              long startTimestamp, long endTimestamp) {
  std::string token = API_TOKEN;
  std::string url = API_ENDPOINT + stockSymbol + "&resolution=" + resolution +
                    "&from=" + std::to_string(startTimestamp) +
                    "&to=" + std::to_string(endTimestamp) + "&token=" + token;
  return callUrl(url);
}

std::string API::getNewsCompany(std::string stockSymbol,
                                std::string startTimestamp,
                                std::string endTimestamp) {
  std::string token = API_TOKEN;
  std::string url = API_NEWSCOMPANY + stockSymbol +
                    "&from=" + startTimestamp +
                    "&to=" + endTimestamp + "&token=" + token;
  return callUrl(url);
}

std::string API::getNewsMarket() {
  std::string token = API_TOKEN;
  std::string url = API_NEWSMARKET + "&token=" + token;
  return callUrl(url);
}

std::string API::callUrl(std::string url) {
  std::string data;
  std::string token = API_TOKEN;
  curl = curl_easy_init();

  if (curl) {
    long httpCode(0); // Initialize the http code to 0, it can't be an int it
    // must be a long int
    // Website settings
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    std::string token_header = "X-Finnhub-Token:" + token;
    // Add the token parameter to the header
    headers = curl_slist_append(headers, token_header.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    // Follow redirections
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // Set the request mode to GET
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    // Handle the data container
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    // Perform the GET request and store the HTTP code
    result = curl_easy_perform(curl);
    // always cleanup
    curl_easy_cleanup(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

    // 200 means successful transfer
    if (httpCode == 200 && result == CURLE_OK) {
      //  contains the requested data
      return data;
    } else if (httpCode == 429) {
      return "";
    }
  }

  return "";
}
