#include "strategygraph.h"
#include "ui_stockgraph.h"
#include "helper/helper.h"
#include <algorithm>

StrategyGraph::StrategyGraph(QWidget *parent) :
  StockGraph(parent) {
  sma20 = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
  sma50 = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
  ema6 = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
  ema11 = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
  lr = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);

  momentumAxisRect = new QCPAxisRect(ui->plot);
  ui->plot->plotLayout()->addElement(1, 0, momentumAxisRect);
  momentumAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 200));
  momentumAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
  momentumAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
  ui->plot->plotLayout()->setRowSpacing(0);
  momentumAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
  momentumAxisRect->setMargins(QMargins(0, 0, 0, 0));

  mom = new QCPGraph(momentumAxisRect->axis(
                       QCPAxis::atBottom), momentumAxisRect->axis(QCPAxis::atLeft));
  mom->setName("Momentum");

  // interconnect x axis ranges of main and bottom axis rects:
  connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)),
          momentumAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
  connect(momentumAxisRect->axis(QCPAxis::atBottom),
          SIGNAL(rangeChanged(QCPRange)),
          ui->plot->xAxis, SLOT(setRange(QCPRange)));

  sma20->setName("SMA 20");
  sma50->setName("SMA 50");
  ema6->setName("EMA 6");
  ema11->setName("EMA 11");
  lr->setName("Linear Regression 10");

  sma20->setPen(QPen(QColor(93, 173, 226), 3));
  sma50->setPen(QPen(QColor(229, 152, 102), 3));
  ema6->setPen(QPen(QColor(93, 63, 106), 3));
  ema11->setPen(QPen(QColor(244, 208, 63), 3));
  lr->setPen(QPen(QColor(38, 166, 91), 3));

  sma20->setVisible(false);
  sma50->setVisible(false);
  ema6->setVisible(false);
  ema11->setVisible(false);
  lr->setVisible(false);
  candleStick->setVisible(false);

  candleStick->removeFromLegend();

  initTimeRange();
  setCandlestickBinSize();
}

StrategyGraph::~StrategyGraph() {
  delete sma20;
  delete sma50;
  delete ema6;
  delete ema11;
  delete lr;
  delete momentumAxisRect;
  delete mom;
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
  momentumAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
  ui->plot->xAxis->setRange(now - 2628288 * 6, now);
  ui->plot->yAxis->setTickLabels(false);
  ui->plot->xAxis->ticker()->setTickCount(10);
//  ui->plot->xAxis->setTicks(
//    false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
  ui->plot->xAxis->setTicker(dateTimeTicker);
//  ui->plot->xAxis->setTickLabelRotation(15);
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

void StrategyGraph::removeAllGraphs() {
  sma20->setVisible(false);
  sma50->setVisible(false);
  ema6->setVisible(false);
  ema11->setVisible(false);
  lr->setVisible(false);
  sma20->removeFromLegend();
  sma50->removeFromLegend();
  ema6->removeFromLegend();
  ema11->removeFromLegend();
  lr->removeFromLegend();
  mom->removeFromLegend();
  momentumAxisRect->setVisible(false);

  ui->plot->plotLayout()->take(momentumAxisRect);
  ui->plot->plotLayout()->simplify();
}

void StrategyGraph::addGraph(QCPGraph *graph) {
  graph->setVisible(true);
  graph->addToLegend();
}

void StrategyGraph::drawSMA(const QVector<double> &timestamp_sma20,
                            const QVector<double> &price_sma20,
                            const QVector<double> &timestamp_sma50,
                            const QVector<double> &price_sma50) {
  sma20->setData(timestamp_sma20, price_sma20, true);
  sma50->setData(timestamp_sma50, price_sma50, true);
  removeAllGraphs();
  addGraph(sma20);
  addGraph(sma50);
}

void StrategyGraph::drawEMA(const QVector<double> &timestamp_ema6,
                            const QVector<double> &price_ema6,
                            const QVector<double> &timestamp_ema11,
                            const QVector<double> &price_ema11) {
  ema6->setData(timestamp_ema6, price_ema6, true);
  ema11->setData(timestamp_ema11, price_ema11, true);
  removeAllGraphs();
  addGraph(ema6);
  addGraph(ema11);
}

void StrategyGraph::drawLR(double slope, double intercept,
                           const QVector<double> &timestamp) {
  QVector<double> lrTimestamp;
  lrTimestamp.append(timestamp[timestamp.size() - 30]);
  lrTimestamp.append(timestamp.back() + 2 * 864000);
  QVector<double> lrPrice;
  lrPrice.append(slope * timestamp[timestamp.size() - 30] + intercept);
  lrPrice.append(slope * (timestamp.back() + 2 * 864000) + intercept);
  lr->setData(lrTimestamp, lrPrice);
  removeAllGraphs();
  addGraph(lr);
}

void StrategyGraph::drawMomentum(const QVector<double> &timestamp,
                                 const QVector<double> &price) {
  removeAllGraphs();
  ui->plot->plotLayout()->addElement(1, 0, momentumAxisRect);
  momentumAxisRect->setVisible(true);
  momentumAxisRect->axis(QCPAxis::atLeft)->setRange(
    *std::min_element(price.begin(), price.end()) * 0.99,
    *std::max_element(price.begin(), price.end()) * 1.01);
  mom->setData(timestamp, price);
}
