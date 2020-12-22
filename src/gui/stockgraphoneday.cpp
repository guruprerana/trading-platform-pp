#include "stockgraphoneday.h"
#include "ui_stockgraph.h"

StockGraphOneDay::StockGraphOneDay(Stock *stock, QWidget *parent) :
  StockGraph(stock, parent) {
  initTimeRange();
  setCandlestickBinSize();
}

StockGraphOneDay::~StockGraphOneDay() {

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
  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key = time.elapsed() /
               1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = -1e9;

  if (key - lastPointKey >= 60) { // 1 minute
    stock->updateDataByMinute();
    QJsonObject dataByMinute = stock->getDataByMinute();

    QVector<double> time, o, h, l, c;
    time = convert_to_vector(dataByMinute, "t");
    o = convert_to_vector(dataByMinute, "o");
    h = convert_to_vector(dataByMinute, "h");
    l = convert_to_vector(dataByMinute, "l");
    c = convert_to_vector(dataByMinute, "c");

    clearData();
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
    lastPointKey = key;
  }
}
