#include "stockgraphonemonth.h"
#include "ui_stockgraph.h"

StockGraphOneMonth::StockGraphOneMonth(Stock *stock, QWidget *parent) :
  StockGraph(stock, parent) {
  initTimeRange();
}

StockGraphOneMonth::~StockGraphOneMonth() {

}

void StockGraphOneMonth::initTimeRange() {
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd/MM/yyyy");
  double now = QDateTime::currentDateTime().toTime_t();
  //2628288 is the number of seconds per month: Here we show a 1-month interval
  ui->plot->xAxis->setRange(now - 2628288, now);
  ui->plot->yAxis->setTickLabels(false);
  ui->plot->xAxis->ticker()->setTickCount(10);
  ui->plot->xAxis->setTicker(dateTimeTicker);
  ui->plot->xAxis->setTickLabelRotation(15);
  ui->plot->rescaleAxes();
  ui->plot->xAxis->scaleRange(1.025, ui->plot->xAxis->range().center());
  ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
}

void StockGraphOneMonth::realtimeDataSlot() {
  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key = time.elapsed() /
               1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = -1e9;

  if (key - lastPointKey >= 60) { // 1 minute
    stock->updateDataByDay();
    QJsonObject dataByDay = stock->getDataByDay();

    QVector<double> time, o, h, l, c;
    time = convert_to_vector(dataByDay, "t");
    o = convert_to_vector(dataByDay, "o");
    h = convert_to_vector(dataByDay, "h");
    l = convert_to_vector(dataByDay, "l");
    c = convert_to_vector(dataByDay, "c");

    clearData();
    double now = QDateTime::currentDateTime().toTime_t();

    for (int i = 0; i < time.size(); i++) {
      if (time[i] >= now - 2628288 && time[i] <= now) {
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
