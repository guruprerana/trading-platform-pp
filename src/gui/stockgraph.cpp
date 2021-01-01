#include "stockgraph.h"
#include "ui_stockgraph.h"
#include "library/qcustomplot.h"
#include <QDateTime>

StockGraph::StockGraph(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockGraph) {
  ui->setupUi(this);

  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                            QCP::iSelectLegend);
  ui->plot->legend->setVisible(true);
  ui->plot->legend->setSelectableParts(QCPLegend::spItems);
  initCandleStick();
  initLineChart();

  // Initialize the tracer
  tracer = new QCPItemTracer(ui->plot);
  tracer->setGraph(lineChart);
  tracer->setStyle(QCPItemTracer::tsCircle);
  tracer->setPen(QPen(Qt::black, 1.5));
  tracer->setBrush(QBrush(Qt::white));
  tracer->setSize(10);
  tracer->setVisible(false);
  tracer->setInterpolating(false);

  // Initialize tracer text
  ui->plot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
  textLabel = new QCPItemText(ui->plot);
  textLabel->position->setParentAnchorX(tracer->anchor("position"));
  textLabel->position->setType(QCPItemPosition::ptViewportRatio);
  textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
  textLabel->position->setCoords(0, 0);
  textLabel->setTextAlignment(Qt::AlignLeft);
  textLabel->setFont(QFont(font().family(), 9));
  textLabel->setClipToAxisRect(false);

  // setup a timer that repeatedly calls StockGraph::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  connect(ui->plot, SIGNAL(mouseMove(QMouseEvent *)), this,
          SLOT(mouse_press(QMouseEvent *)));
  dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
  ui->plot->replot();
}

StockGraph::~StockGraph() {
  delete ui;
  delete stock;
  delete lineChart;
  delete candleStick;
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
//  lineChart->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
//                             QPen(Qt::black, 1.5), QBrush(Qt::white), 3));
  lineChart->setLineStyle(QCPGraph::lsLine);
  lineChart->setPen(QPen(QColor(120, 120, 120), 3));
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
  candleStick->setName("Candlestick");
}

void StockGraph::mouse_press(QMouseEvent *event) {
  if (timestamp.isEmpty() || close.isEmpty()) {
    return;
  }

  double coordX = ui->plot->xAxis->pixelToCoord(event->pos().x());
  tracer->setVisible(true);
  tracer->setGraphKey(coordX);

  //NEW CODE
  textLabel->setText(
    "Date: " + QDateTime::fromTime_t(int(
                                       tracer->position->key())).toString("dd/MM/yyyy hh:mm:ss") +
    "\nPrice: " + QString::number(tracer->position->value()) + "$"
  );
  //END CODE
  ui->plot->replot();
}

void StockGraph::plot() {
  if (timestamp.isEmpty() || close.isEmpty()) {
    return;
  }

  lineChart->setData(timestamp, close);
  candleStick->setData(timestamp, open, high, low, close);
  ui->plot->xAxis->setRange(timestamp[0],
                            timestamp[timestamp.length() - 1]);
  double ymin = *std::min_element(low.begin(), low.end());
  double ymax = *std::max_element(high.begin(), high.end());
  double yrange = ymax - ymin;

  ui->plot->yAxis->setRange(
    std::max(0.0, ymin - yrange * 0.1),
    ymax + yrange * 0.1
  );
  //ui->plot->replot();
  //ui->plot->update(); // updates data
  ui->plot->yAxis->setTickLabels(true);
}
