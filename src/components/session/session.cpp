#include "session.h"

#include <QHashIterator>
#include <QFile>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>

Session::Session() {
  loadFromFile("save.json");
}

Session::~Session() {
  saveToFile("save.json");

  for (int i = 0; i < portfolios.size(); ++i) {
    delete portfolios.value(i);
  }

  QHashIterator<QString, Stock *> i(stocks);

  while (i.hasNext()) {
    i.next();
    delete i.value();
  }
}

void Session::loadFromFile(const QString &filename) {
  QFile jsonFile(filename);
  jsonFile.open(QFile::ReadOnly);

  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFile.readAll());

  if (!(jsonDocument.isNull() && jsonDocument.isArray())) {
    // cannot load
    return;
  }

  QJsonArray portfoliosJson = jsonDocument.array();

  for (int i = 0; i < portfoliosJson.size(); i++) {
    if (portfoliosJson.at(i).isObject()) {
      Portfolio *portfolio = new Portfolio();
      portfolio->load(portfoliosJson.at(i).toObject());
      portfolios.push_back(portfolio);

      // initialize all stock in the watchlist of each portfolio

      QStringList stocks_to_initialize = portfolio->getWatchList();

      for (int i = 0; i < stocks_to_initialize.size(); i++) {
        stocks.insert(stocks_to_initialize.at(i),
                      new Stock(stocks_to_initialize.at(i).toStdString()));
      }
    }
  }
}

void Session::saveToFile(const QString &filename) const {
  QFile jsonFile(filename);
  jsonFile.open(QFile::WriteOnly);

  QJsonArray portfoliosJson;

  for (int i = 0; i < portfolios.size(); ++i) {
    QJsonObject portfolioJson;
    portfolios.at(i)->save(portfolioJson);
    portfoliosJson.push_back(portfolioJson);
  }

  QJsonDocument jsonDocument(portfoliosJson);

  jsonFile.write(jsonDocument.toJson());
}

Portfolio *Session::getPortfolio(QString &id) const {
  for (int i = 0; i < portfolios.size(); ++i) {
    if (portfolios.at(i)->getId() == id) {
      return portfolios.at(i);
    }
  }

  return nullptr;
}

void Session::addPortfolio(Portfolio *newPortfolio) {
  portfolios.push_back(newPortfolio);
}

Stock *Session::addStock(QString &symbol) {
  if (!stocks.contains(symbol)) {
    stocks.insert(symbol, new Stock(symbol.toStdString()));
  }

  return stocks[symbol];
}
