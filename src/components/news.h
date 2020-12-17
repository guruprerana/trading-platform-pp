#ifndef NEWS_H
#define NEWS_H

#include <QJsonArray>

class News {
 private:
  QJsonArray marketNews;

 public:
  News();
  ~News();

  QJsonArray getMarketNews();
  void updateMarketNews();

};
#endif // NEWS_H
