#ifndef PORTFOLIOWIDGET_H
#define PORTFOLIOWIDGET_H

#include <QWidget>
#include "../../components/portfolio.h"

namespace Ui {
class PortfolioWidget;
}

class PortfolioWidget : public QWidget {
  Q_OBJECT

 public:
  explicit PortfolioWidget(Portfolio *portfolio, QWidget *parent = nullptr);
  ~PortfolioWidget();

 signals:
  void portfolioClicked(Portfolio *portfolio);

 private slots:
  void on_portfolioName_released();

 private:
  Ui::PortfolioWidget *ui;
  Portfolio *portfolio;
};

#endif // PORTFOLIOWIDGET_H
