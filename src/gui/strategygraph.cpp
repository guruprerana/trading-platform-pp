#include "strategygraph.h"
#include "ui_stockgraph.h"
#include "helper/helper.h"

StrategyGraph::StrategyGraph(QWidget *parent) :
  StockGraph(parent) {
  initTimeRange();
  setCandlestickBinSize();
  sma20 = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
  sma50 = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);

  sma20->setName("SMA 20");
  sma50->setName("SMA 50");

  sma20->setPen(QPen(QColor(93, 173, 226), 3));
  sma50->setPen(QPen(QColor(229, 152, 102), 3));

  sma20->setVisible(false);
  sma50->setVisible(false);
  candleStick->setVisible(false);

  candleStick->removeFromLegend();
}

StrategyGraph::~StrategyGraph() {

}

void StrategyGraph::setStock(Stock *other_stock) {
  stock = other_stock;
  stock->updateDataByDay();

  QJsonObject dataByDay = stock->getDataByDay();
  timestamp = helper::convert_to_vector(dataByDay, "t");
  open = helper::convert_to_vector(dataByDay, "o");
  high = helper::convert_to_vector(dataByDay, "h");
  low = helper::convert_to_vector(dataByDay, "l");
  close = helper::convert_to_vector(dataByDay, "c");

  lineChart->setData(timestamp, close);
  plot();
}

void StrategyGraph::updateData(bool firstTime = false) {

}

void StrategyGraph::initTimeRange() {
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

void StrategyGraph::setCandlestickBinSize() {
  candleStick->setWidth(3600 * 24 * 0.5);
}

void StrategyGraph::realtimeDataSlot() {
  //  if (stock == nullptr) {
  //    return;
  //  }

  //  static QTime time(QTime::currentTime());
  //  //calculate two new data points:
  //  double key = time.elapsed() /
  //               1000.0; // time elapsed since start of demo, in seconds
  //  static double lastPointKey = -1e9;

  //  if (key - lastPointKey >= 250) { // 250 seconds
  //    updateData();
  //    lastPointKey = key;
  //  }
}

void StrategyGraph::drawSMA(const QVector<double> &timestamp_sma20,
                            const QVector<double> &price_sma20,
                            const QVector<double> &timestamp_sma50,
                            const QVector<double> &price_sma50) {
  sma20->setData(timestamp_sma20, price_sma20, true);
  sma50->setData(timestamp_sma50, price_sma50, true);
  sma20->setVisible(true);
  sma50->setVisible(true);
}
