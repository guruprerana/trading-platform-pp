#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "stockdashboard.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget {
  Q_OBJECT

 public:
  explicit HomePage(QWidget *parent = nullptr);
  ~HomePage();

 private:
  Ui::HomePage *ui;
  StockDashboard *stockDashboard;
};

#endif // HOMEPAGE_H
