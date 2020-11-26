#include "chooseportfolio.h"
#include "ui_chooseportfolio.h"

ChoosePortfolio::ChoosePortfolio(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ChoosePortfolio) {
  ui->setupUi(this);
}

ChoosePortfolio::~ChoosePortfolio() {
  delete ui;
}
