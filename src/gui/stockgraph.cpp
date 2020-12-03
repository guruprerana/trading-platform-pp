#include "stockgraph.h"
#include "ui_stockgraph.h"

StockGraph::StockGraph(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockGraph) {
  ui->setupUi(this);
}

StockGraph::~StockGraph() {
  delete ui;
}
