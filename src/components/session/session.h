#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QHash>
#include <QString>
#include "../portfolio/portfolio.h"
#include "../stock.h"

class Session {
 public:
  Session();
  ~Session();

  Portfolio *getPortfolio(QString &id) const;
  void addPortfolio(Portfolio *newPortfolio);

  Stock *addStock(QString &symbol);
  Stock *getStock(QString &symbol);

  void loadFromFile(const QString &filename);
  void saveToFile(const QString &filename) const;

 private:
  QVector<Portfolio *> portfolios;

  // store the instances of the stocks in a hash-table indexed by symbol string
  QHash<QString, Stock *> stocks;

};

#endif // SESSION_H
