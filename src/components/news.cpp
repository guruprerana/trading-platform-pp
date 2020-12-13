#include "news.h"
#include "../api/api.h"

News::News() {
  marketNews = "";
}

News::~News() {

}

std::string News::getMarketNews() {
  return marketNews;
}

void News::updateMarketNews() {
  API *api = new API();
  std::string apiResponse = api->getNewsMarket();
  marketNews = apiResponse;
}
