#ifndef CHOOSEPORTFOLIO_H
#define CHOOSEPORTFOLIO_H

#include <QWidget>
#include <QVector>
#include <QHBoxLayout>
#include "../components/portfolio.h"

namespace Ui {
class ChoosePortfolio;
}

class ChoosePortfolio : public QWidget {
  Q_OBJECT

 public:
  explicit ChoosePortfolio(QVector<Portfolio *> &portfolios,
                           QWidget *parent = nullptr);
  ~ChoosePortfolio();

 signals:
  void createNewPortfolio();
  void portfolioChosen(Portfolio *portfolio);

 private slots:
  void on_pushButton_released();

 private:
  Ui::ChoosePortfolio *ui;
  QVector<Portfolio *> portfolios;
  QHBoxLayout *layout;
};

#endif // CHOOSEPORTFOLIO_H
