#ifndef NEWORDER_H
#define NEWORDER_H

#include "../components/trading_order.h"

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QVariant>
#include <QWidget>
#include <QVBoxLayout>

#include "../components/portfolio.h"
#include "../components/stock.h"

namespace Ui {
class NewOrder;
}

class NewOrder : public QWidget {
  Q_OBJECT

 public:
  explicit NewOrder(QWidget *parent = nullptr);
  ~NewOrder();

  bool write(TradingOrder &trading_order);
  void updateWatchlistStocks(QVector<Stock *> watchlistStocks);
  void setCurrentPortfolio(Portfolio *portfolio);
  void updatePricePerQuantityAndEstimateValue();

 signals:
  void newOrderCreated(TradingOrder *newOrder);
  void updatePricePerQuantity(qreal price);

 public slots:
  void computePerformanceTable(Portfolio *portfolio);

 private slots:
  void on_orderPushButton_released();
  void on_cancelPushButton_pressed();

  void on_quantityValueSpinBox_valueChanged(double arg1);

  void setErrorText(QString error);
  void on_symbolComboBox_currentTextChanged(const QString &symbol);

  void on_actionsValueComboBox_currentTextChanged(const QString &arg1);

 private:
  Ui::NewOrder *ui;
  void setDefault();

  QVector<Stock *> watchlistStocks;
  Portfolio *currentPortfolio;
};

#endif // NEWORDER_H
