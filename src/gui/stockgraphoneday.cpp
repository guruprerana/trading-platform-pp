#include "stockgraphoneday.h"
#include "ui_stockgraph.h"

StockGraphOneDay::StockGraphOneDay(QWidget *parent) :
  StockGraph(parent) {
  initTimeRange();
  setCandlestickBinSize();
}

StockGraphOneDay::~StockGraphOneDay() {

}

void StockGraphOneDay::setStock(Stock *other_stock) {
  stock = other_stock;
  clearData();
  lineChart->setData({}, {});
  candleStick->setData({}, {}, {}, {}, {});
  updateData();
}

void StockGraphOneDay::updateData() {
  stock->updateDataByMinute();
  int sz = stock->getDataByMinuteSize();
  int oldSz = timestamp.size();

  for (int i = oldSz; i < sz; i++) {
    auto curData = stock->getDataByMinute(i);
    timestamp.append(curData["h"]);
    open.append(curData["o"]);
    high.append(curData["h"]);
    low.append(curData["l"]);
    close.append(curData["c"]);
    lineChart->addData(curData["t"], curData["c"]);
    candleStick->addData(curData["t"], curData["o"], curData["h"], curData["l"],
                         curData["c"]);
  }

  plot();
}

void StockGraphOneDay::initTimeRange() {
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd/MM hh:mm");
  double now = QDateTime::currentDateTime().toTime_t();
  // 86400 is the number of seconds per day: Here we show a 1-day interval
  ui->plot->xAxis->setRange(now - 86400, now);
  ui->plot->yAxis->setTickLabels(false);
  ui->plot->xAxis->ticker()->setTickCount(10);
  ui->plot->xAxis->setTicker(dateTimeTicker);
  ui->plot->xAxis->setTickLabelRotation(15);
  ui->plot->rescaleAxes();
  ui->plot->xAxis->scaleRange(1.025, ui->plot->xAxis->range().center());
  ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
}

void StockGraphOneDay::setCandlestickBinSize() {
  candleStick->setWidth(60 * 0.5);
}

void StockGraphOneDay::realtimeDataSlot() {
  if (stock == nullptr) {
    return;
  }

  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key = time.elapsed() /
               1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = -1e9;

  if (key - lastPointKey >= 60) { // 1 minute
    updateData();
    lastPointKey = key;
  }
}
