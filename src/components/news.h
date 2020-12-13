#ifndef NEWS_H
#define NEWS_H

#include <string>

class News {
 private:
  std::string marketNews;

 public:
  News();
  ~News();

  std::string getMarketNews();
  void updateMarketNews();

};
#endif // NEWS_H
