#ifndef STOCKPERFORMANCEROW_H
#define STOCKPERFORMANCEROW_H

#include "components/portfolio.h"
#include <QWidget>
#include <QString>

namespace Ui {
class StockPerformanceRow;
}

class StockPerformanceRow : public QWidget {
  Q_OBJECT

 public:
  explicit StockPerformanceRow(QWidget *parent = nullptr);
  ~StockPerformanceRow();

  void from(Portfolio *portfolio, qint32 nLabel, QString symbol);
 private:
  Ui::StockPerformanceRow *ui;
};

#endif // STOCKPERFORMANCEROW_H
