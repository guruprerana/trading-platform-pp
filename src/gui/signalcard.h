#ifndef SIGNALCARD_H
#define SIGNALCARD_H

#include <QWidget>

namespace Ui {
class SignalCard;
}

class SignalCard : public QWidget {
  Q_OBJECT

 public:
  explicit SignalCard(double timestamp, bool buy, QWidget *parent = nullptr);
  ~SignalCard();

 private:
  Ui::SignalCard *ui;
};

#endif // SIGNALCARD_H
