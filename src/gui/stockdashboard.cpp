#include "stockdashboard.h"
#include "ui_stockdashboard.h"

StockDashboard::StockDashboard(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockDashboard) {
  ui->setupUi(this);

  stockGraph = new StockGraph();

  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(stockGraph);
  this->setLayout(layout);
}

StockDashboard::~StockDashboard() {
  delete ui;
  delete stockGraph;
}
