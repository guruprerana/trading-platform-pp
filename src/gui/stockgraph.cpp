#include "stockgraph.h"
#include "ui_stockgraph.h"

StockGraph::StockGraph(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockGraph) {
  ui->setupUi(this);

  stock = new Stock("AAPL");
}

StockGraph::~StockGraph() {
  delete ui;
  delete stock;
}
