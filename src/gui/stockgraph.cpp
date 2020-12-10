#include "stockgraph.h"
#include "ui_stockgraph.h"
#include "library/qcustomplot.h"

#include <iostream>
StockGraph::StockGraph(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StockGraph) {
  ui->setupUi(this);

  stock = new Stock("AAPL");

  ui->plot->addGraph();
  ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, QPen(Qt::red, 1.5), QBrush(Qt::darkRed), 3));
  ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui->plot->graph(0)->setPen(QPen(Qt::red));
  ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd/MM/yyyy");
  double now = QDateTime::currentDateTime().toTime_t();
  ui->plot->xAxis->setRange(now-2628288*6, now+2628288*6); //2628288 is the number of seconds per month: Here we show a 6-month interval
  ui->plot->yAxis->setTickLabels(false);
  ui->plot->xAxis->ticker()->setTickCount(10);
  ui->plot->xAxis->setTicker(dateTimeTicker);
  ui->plot->xAxis->setTickLabelRotation(15);
  ui->plot->rescaleAxes();
  ui->plot->xAxis->scaleRange(1.025, ui->plot->xAxis->range().center());
  ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
  stock->updateDataByDay();
  QJsonObject dataByDay=stock->getDataByDay();
  //Converts Json data to Vector
  timestamp=convert_to_vector(dataByDay,"t"); //Get timestamp values
  high=convert_to_vector(dataByDay,"h"); //Get high values corresponding to timestamp
  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
  qDebug()<<"rayen"<<high;
  //ui->plot->graph(0)->addData(timestamp,high);
  ui->plot->replot();
}
StockGraph::~StockGraph() {
  delete ui;
  delete stock;
  clearData();
}
void StockGraph::clearData(){
    timestamp.clear();
    high.clear();
}
void  StockGraph::plot(){
        ui->plot->graph(0)->setData(timestamp,high);
        //ui->plot->xAxis->setRangeUpper(*std::max_element(timestamp.begin(),timestamp.end())*1.25);
        //ui->plot->xAxis->setRange(timestamp[0], timestamp[timestamp.length()-1]);
        //ui->plot->yAxis->setRangeUpper(*std::max_element(high.begin(),high.end())*1.25);
        //ui->plot->yAxis->setRange(*std::min_element(high.begin(), high.end()),*std::max_element(high.begin(),high.end()));
        ui->plot->graph(0)->rescaleAxes();
        ui->plot->replot();
        ui->plot->update(); //updates data
        ui->plot->yAxis->setTickLabels(true);

    }




void StockGraph::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
   //calculate two new data points:
 double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
 if (key-lastPointKey > 2) // at most add point every 6 s
  {     stock->updateDataByDay();
        QJsonObject dataByDay=stock->getDataByDay();
        QVector<double> time,h;
        time=convert_to_vector(dataByDay,"t");
        h=convert_to_vector(dataByDay,"h");
        if(not time.isEmpty() && not h.isEmpty()){
        for (int i=0;i<std::min(time.count(),h.count());i++){

            if (  not std::count(timestamp.begin(), timestamp.end(), time[i])){
                timestamp.append(time[i]);
                high.append(h[i]);


            }
        }
        plot();}
  }}

QVector<double> convert_to_vector(QJsonObject j, std::string k)
{   QVariantMap j_map=j.toVariantMap();
    QVariantList j_list =j_map[k.c_str()].toList();
    QVector<double> q;
    for (int i=0;i<j_list.count();i++)
    {
        q.append(j_list[i].toDouble());
    }
    return q;

}


