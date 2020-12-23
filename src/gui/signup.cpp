#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::SignUp) {
  ui->setupUi(this);

  ui->errorLabel->hide();
}

SignUp::~SignUp() {
  delete ui;
}

void SignUp::showError(const QString &errorMessage) {
  ui->errorLabel->setText(errorMessage);
  ui->errorLabel->show();
}

void SignUp::on_submitButton_released() {
  // submit button clicked so create new user
  QString id = ui->portfolioNameTextEdit->toPlainText();

  if (id.size() == 0) {
    showError("Portfolio name cannot be empty");
    return;
  }

  qreal initialAmount = ui->initialAmountSpinBox->value();

  if (initialAmount < 0) {
    showError("Please choose a non-negative initial amount");
    return;
  }

  QStringList watchlist = ui->selectWatchListWidget->getSelectedWatchList();

  if (watchlist.size() == 0) {
    showError("Please choose at least one stock for the watchlist");
    return;
  }

  emit signUpWithDetails(id, initialAmount, watchlist);

  // clear all the fields once emitted
  ui->errorLabel->hide();
  ui->portfolioNameTextEdit->clear();
  ui->initialAmountSpinBox->setValue(0.0);
}
