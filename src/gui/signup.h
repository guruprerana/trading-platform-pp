#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QString>
#include <QStringList>


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
  void showError(const QString &errorMessage);

 signals:
  // need to add the necessary details as arguments to this signal
  void signUpWithDetails(QString id, qreal initialAmount, QStringList watchlist);

 private slots:
  void on_submitButton_released();
};

#endif // SIGNUP_H
