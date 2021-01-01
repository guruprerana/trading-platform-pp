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
  updateData();
}

void StockGraphOneDay::updateData() {
  QMap<std::string, QVector<double>> dataByMinute = stock->updateDataByMinute();

  if (dataByMinute.isEmpty() and timestamp.isEmpty()) {
    dataByMinute = stock->getDataByMinute();
  }

  QVector<double> time, o, h, l, c;
  time = dataByMinute["t"];
  o = dataByMinute["o"];
  h = dataByMinute["h"];
  l = dataByMinute["l"];
  c = dataByMinute["c"];

  double now = QDateTime::currentDateTime().toTime_t();

  // 86400 is the number of seconds per day: Here we show a 1-day interval
  ui->plot->xAxis->setRange(now - 86400, now);

  for (int i = 0; i < time.size(); i++) {
    if (time[i] >= now - 86400 && time[i] <= now) {
      timestamp.append(time[i]);
      open.append(o[i]);
      high.append(h[i]);
      low.append(l[i]);
      close.append(c[i]);
    }
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
