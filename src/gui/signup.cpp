#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SignUp) {
  ui->setupUi(this);
}

SignUp::~SignUp() {
  delete ui;
}

void SignUp::on_submitButton_released() {
  // submit button clicked so create new user

  emit signUpWithDetails();

  // clear all the fields once emitted
  ui->firstNameTextEdit->clear();
  ui->lastNameTextEdit->clear();
  ui->watchlistTextEdit->clear();
}
