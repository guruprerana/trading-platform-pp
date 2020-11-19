#ifndef API_H
#define API_H

#include <iostream>
#include <map>

class API {
 public:
  API();
  ~API();

  std::map <std::string, double> getStockData(std::string stockSymbol,
      long startTimestamp, long endTimestamp);

 private:
  // CURL object here
};

#endif // API_H
