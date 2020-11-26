#ifndef CHOOSEUSER_H
#define CHOOSEUSER_H

#include <QWidget>

namespace Ui {
class ChooseUser;
}

class ChooseUser : public QWidget {
  Q_OBJECT

 public:
  explicit ChooseUser(QWidget *parent = nullptr);
  ~ChooseUser();

 private:
  Ui::ChooseUser *ui;

 signals:
  // again, need to add argument of user which will be chosen
  void userChosen();
};

#endif // CHOOSEUSER_H
