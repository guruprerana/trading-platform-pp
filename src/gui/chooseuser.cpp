#include "chooseuser.h"
#include "ui_chooseuser.h"

ChooseUser::ChooseUser(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ChooseUser) {
  ui->setupUi(this);
}

ChooseUser::~ChooseUser() {
  delete ui;
}
