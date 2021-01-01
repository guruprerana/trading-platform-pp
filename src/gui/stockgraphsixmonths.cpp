#include "stockgraphsixmonths.h"
#include "ui_stockgraph.h"
#include "helper/helper.h"

StockGraphSixMonths::StockGraphSixMonths(QWidget *parent) :
  StockGraph(parent) {
  initTimeRange();
  setCandlestickBinSize();
}

StockGraphSixMonths::~StockGraphSixMonths() {

}

void StockGraphSixMonths::setStock(Stock *other_stock) {
  stock = other_stock;
  updateData();
}

void StockGraphSixMonths::updateData() {
  stock->updateDataByDay();
  QJsonObject dataByDay = stock->getDataByDay();

  QVector<double> time, o, h, l, c;
  time = helper::convert_to_vector(dataByDay, "t");
  o = helper::convert_to_vector(dataByDay, "o");
  h = helper::convert_to_vector(dataByDay, "h");
  l = helper::convert_to_vector(dataByDay, "l");
  c = helper::convert_to_vector(dataByDay, "c");

  double now = QDateTime::currentDateTime().toTime_t();
  //2628288 is the number of seconds per month: Here we show a 6-month interval
  ui->plot->xAxis->setRange(now - 2628288 * 6, now);

  clearData();

  for (int i = 0; i < time.size(); i++) {
    timestamp.append(time[i]);
    open.append(o[i]);
    high.append(h[i]);
    low.append(l[i]);
    close.append(c[i]);
  }

  plot();
}

void StockGraphSixMonths::initTimeRange() {
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd/MM/yyyy");
  double now = QDateTime::currentDateTime().toTime_t();
  //2628288 is the number of seconds per month: Here we show a 6-month interval
  ui->plot->xAxis->setRange(now - 2628288 * 6, now);
  ui->plot->yAxis->setTickLabels(false);
  ui->plot->xAxis->ticker()->setTickCount(10);
  ui->plot->xAxis->setTicker(dateTimeTicker);
  ui->plot->xAxis->setTickLabelRotation(15);
  ui->plot->rescaleAxes();
  ui->plot->xAxis->scaleRange(1.025, ui->plot->xAxis->range().center());
  ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
}

void StockGraphSixMonths::setCandlestickBinSize() {
  candleStick->setWidth(3600 * 24 * 0.5);
}

void StockGraphSixMonths::realtimeDataSlot() {
  if (stock == nullptr) {
    return;
  }

  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key = time.elapsed() /
               1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = -1e9;

  if (key - lastPointKey >= 250) { // 250 seconds
    updateData();
    lastPointKey = key;
  }
}
