#include "stockdashboard.h"
#include "ui_stockdashboard.h"

StockDashboard::StockDashboard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockDashboard) {
  ui->setupUi(this);
}

StockDashboard::~StockDashboard() {
  delete ui;
}
