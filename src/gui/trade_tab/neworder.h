#ifndef NEWORDER_H
#define NEWORDER_H

#include <QWidget>

namespace Ui {
class NewOrder;
}

class NewOrder : public QWidget {
  Q_OBJECT

 public:
  explicit NewOrder(QWidget *parent = nullptr);
  ~NewOrder();

 public slots:

 signals:

 private:
  Ui::NewOrder *ui;
};

#endif // NEWORDER_H
