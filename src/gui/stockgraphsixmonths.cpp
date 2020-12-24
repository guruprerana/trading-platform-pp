#include "stockgraphsixmonths.h"
#include "ui_stockgraph.h"

StockGraphSixMonths::StockGraphSixMonths(Stock *stock, QWidget *parent) :
  StockGraph(stock, parent) {
  initTimeRange();
  setCandlestickBinSize();
}

StockGraphSixMonths::~StockGraphSixMonths() {

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
  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key = time.elapsed() /
               1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = -1e9;

  if (key - lastPointKey >= 250) { // 250 seconds
    stock->updateDataByDay();
    QJsonObject dataByDay = stock->getDataByDay();

    QVector<double> time, o, h, l, c;
    time = convert_to_vector(dataByDay, "t");
    o = convert_to_vector(dataByDay, "o");
    h = convert_to_vector(dataByDay, "h");
    l = convert_to_vector(dataByDay, "l");
    c = convert_to_vector(dataByDay, "c");

    for (int i = timestamp.size(); i < time.size(); i++) {
      timestamp.append(time[i]);
      open.append(o[i]);
      high.append(h[i]);
      low.append(l[i]);
      close.append(c[i]);
    }

    plot();
    lastPointKey = key;
  }
}
