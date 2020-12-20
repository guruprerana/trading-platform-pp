#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>

namespace Ui {
class SignUp;
}

class SignUp : public QWidget {
  Q_OBJECT

 public:
  explicit SignUp(QWidget *parent = nullptr);
  ~SignUp();

 private:
  Ui::SignUp *ui;

 signals:
  // need to add the necessary details as arguments to this signal
  void signUpWithDetails();

 private slots:
  void on_submitButton_released();
};

#endif // SIGNUP_H
