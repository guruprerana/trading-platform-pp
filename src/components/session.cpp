#include "session.h"

#include <QHashIterator>
#include <QFile>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>

Session::Session() {
  loadFromFile(SAVE_FILE_NAME);
}

Session::~Session() {
  saveToFile(SAVE_FILE_NAME);

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

  if (!jsonFile.open(QFile::ReadOnly)) {
    qWarning("Could not open save file.");
    return;
  }

  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFile.readAll());

  if (jsonDocument.isNull() || !jsonDocument.isArray()) {
    qWarning("File might not have proper JSON structure or is empty.");
    return;
  }

  QJsonArray portfoliosJson = jsonDocument.array();

  for (int i = 0; i < portfoliosJson.size(); i++) {
    if (portfoliosJson.at(i).isObject()) {
      Portfolio *portfolio = new Portfolio();
      portfolio->load(portfoliosJson.at(i).toObject());
      portfolios.push_back(portfolio);

      // right now we just set current portfolio to last saved
      // portfolio. will change with implementation of
      // choose portfolio screen
      currentPortfolio = portfolio;

      // initialize all stock in the watchlist of each portfolio

      QVector<Stock *> stocks;

      for (auto s : portfolio->getWatchList()) {
        stocks.push_back(addStock(s));
      }

      portfolio->updateWatchlistStocks(stocks);
    }
  }
}

void Session::saveToFile(const QString &filename) const {
  QFile jsonFile(filename);

  if (!jsonFile.open(QFile::WriteOnly)) {
    qWarning("Could not open save file.");
    return;
  }

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

  QVector<Stock *> stocks;
  addStocks(newPortfolio->getWatchList());

  for (auto s : newPortfolio->getWatchList()) {
    stocks.push_back(addStock(s));
  }

  newPortfolio->updateWatchlistStocks(stocks);

  // change current portfolio
  currentPortfolio = newPortfolio;
}

Stock *Session::addStock(QString symbol) {
  if (!stocks.contains(symbol)) {
    stocks.insert(symbol, new Stock(symbol.toStdString()));
  }

  return stocks[symbol];
}

void Session::addStocks(QStringList &symbols) {
  for (int i = 0; i < symbols.size(); i++) {
    addStock(symbols.at(i));
  }
}

Stock *Session::getStock(QString &symbol) {
  if (!stocks.contains(symbol)) {
    return nullptr;
  }

  return stocks[symbol];
}

QVector<Stock *> Session::getCurrentWatchlistStocks() {
  QVector<Stock *> stocks;

  if (currentPortfolio == nullptr) {
    return stocks;
  }

  QStringList symbols = currentPortfolio->getWatchList();

  for (int i = 0; i < symbols.size(); i++) {
    stocks.push_back(addStock(symbols.at(i)));
  }

  return stocks;
}
