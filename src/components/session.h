#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QHash>
#include <QString>
#include "portfolio.h"
#include "stock.h"

class Session {
 public:
  Session();
  ~Session();

  const QString SAVE_FILE_NAME = "save.json";

  Portfolio *getCurrentPortfolio() const {
    if (currentPortfolio == nullptr) {
      qWarning("Current portfolio not set.");
    }

    return currentPortfolio;
  }

  QVector<Stock *> getCurrentWatchlistStocks();

  Portfolio *getPortfolio(QString &id) const;
  void addPortfolio(Portfolio *newPortfolio);

  Stock *addStock(QString symbol);
  void addStocks(QStringList &symbols);

  Stock *getStock(QString &symbol);

  void loadFromFile(const QString &filename);
  void saveToFile(const QString &filename) const;

 private:
  QVector<Portfolio *> portfolios;
  Portfolio *currentPortfolio = nullptr;

  // store the instances of the stocks in a hash-table indexed by symbol string
  QHash<QString, Stock *> stocks;

};

#endif // SESSION_H
