#include "stockgraph.h"
#include "ui_stockgraph.h"
#include "library/qcustomplot.h"

StockGraph::StockGraph(Stock *stock, QWidget *parent) :
  stock(stock),
  QWidget(parent),
  ui(new Ui::StockGraph) {
  ui->setupUi(this);

  ui->plot->legend->setVisible(true);
  ui->plot->legend->setSelectableParts(QCPLegend::spItems);

  initCandleStick();
  initLineChart();

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

  // Get data from stock
  stock->updateDataByDay();
  QJsonObject dataByDay = stock->getDataByDay();

  // Convert Json data to Vector
  timestamp = convert_to_vector(dataByDay, "t");
  open = convert_to_vector(dataByDay, "o");
  high = convert_to_vector(dataByDay, "h");
  low = convert_to_vector(dataByDay, "l");
  close = convert_to_vector(dataByDay, "c");

  // setup a timer that repeatedly calls StockGraph::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
  //ui->plot->graph(0)->addData(timestamp,high);
  ui->plot->replot();
}

StockGraph::~StockGraph() {
  delete ui;
  clearData();
}

void StockGraph::clearData() {
  timestamp.clear();
  open.clear();
  high.clear();
  low.clear();
  close.clear();
}

void StockGraph::initLineChart() {
  lineChart = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
  lineChart->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
                             QPen(Qt::black, 1.5), QBrush(Qt::white), 3));
  lineChart->setLineStyle(QCPGraph::lsLine);
  lineChart->setPen(QPen(QColor(120, 120, 120), 2));
  lineChart->keyAxis()->setUpperEnding(QCPLineEnding::esSpikeArrow);
  lineChart->valueAxis()->setUpperEnding(QCPLineEnding::esSpikeArrow);

  QBrush shadowBrush(QColor(0, 0, 0), Qt::Dense7Pattern);
  lineChart->setBrush(shadowBrush);
  lineChart->setName("Line chart");
}

void StockGraph::initCandleStick() {
  candleStick = new QCPFinancial(ui->plot->xAxis,
                                 ui->plot->yAxis);
  candleStick->setChartStyle(QCPFinancial::csCandlestick);
  candleStick->setData(timestamp, open, high, low, close);
  candleStick->setTwoColored(true);
  candleStick->setWidth(3600 * 24 * 0.5);
  candleStick->setName("Candlestick");
}

void StockGraph::plot() {
  lineChart->setData(timestamp, close);
  candleStick->setData(timestamp, open, high, low, close);
  ui->plot->xAxis->setRange(timestamp[0],
                            timestamp[timestamp.length() - 1]);
  ui->plot->yAxis->setRange(
    std::max(0.0, *std::min_element(low.begin(),
                                    low.end()) * 0.8),
    *std::max_element(high.begin(), high.end()) * 1.25);
  ui->plot->replot();
  ui->plot->update(); // updates data
  ui->plot->yAxis->setTickLabels(true);
}

void StockGraph::realtimeDataSlot() {
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

    for (int i = timestamp.size(); i < time.size(); i++) {
      timestamp.append(time[i]);
      open.append(o[i]);
      high.append(h[i]);
      low.append(l[i]);
      close.append(c[i]);
    }

    plot();
  }
}

QVector<double> convert_to_vector(QJsonObject j, std::string k) {
  QVariantMap j_map = j.toVariantMap();
  QVariantList j_list = j_map[k.c_str()].toList();
  QVector<double> q;

  for (int i = 0; i < j_list.count(); i++) {
    q.append(j_list[i].toDouble());
  }

  return q;
}


