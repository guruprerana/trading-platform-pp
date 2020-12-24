#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HomePage) {
  ui->setupUi(this);

  stockDashboard = new StockDashboard();
  ui->verticalLayout->addWidget(stockDashboard);
}

HomePage::~HomePage() {
  delete ui;
  delete stockDashboard;
}
