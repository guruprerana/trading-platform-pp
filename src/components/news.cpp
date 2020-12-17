#include "news.h"
#include "api/api.h"
#include "helper/helper.h"


News::News() {
  marketNews = QJsonArray();
}

News::~News() {

}

QJsonArray News::getMarketNews() {
  return marketNews;
}

void News::updateMarketNews() {
  API *api = new API();
  std::string apiResponse = api->getNewsMarket();
  marketNews = helper::convertStringToQJsonArray(apiResponse);
}
