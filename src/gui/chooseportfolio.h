#ifndef CHOOSEPORTFOLIO_H
#define CHOOSEPORTFOLIO_H

#include <QWidget>

namespace Ui {
class ChoosePortfolio;
}

class ChoosePortfolio : public QWidget {
  Q_OBJECT

 public:
  explicit ChoosePortfolio(QWidget *parent = nullptr);
  ~ChoosePortfolio();

 private:
  Ui::ChoosePortfolio *ui;
};

#endif // CHOOSEPORTFOLIO_H
