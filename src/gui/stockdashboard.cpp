#include "stockdashboard.h"
#include "ui_stockdashboard.h"

StockDashboard::StockDashboard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockDashboard) {
  ui->setupUi(this);

  stockGraph = new StockGraph();

  ui->verticalLayout->addWidget(stockGraph);
}

StockDashboard::~StockDashboard() {
  delete ui;
  delete stockGraph;
}
