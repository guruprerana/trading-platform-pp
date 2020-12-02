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
