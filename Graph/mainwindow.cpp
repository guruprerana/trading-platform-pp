#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Graph Test");
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
    stock.updateDataByDay();
    QJsonObject dataByDay=stock.getDataByDay();
    //Converts Json data to Vector
    timestamp=convert_to_vector(dataByDay,"t"); //Get timestamp values
    high=convert_to_vector(dataByDay,"h"); //Get high values corresponding to timestamp
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
    qDebug()<<"rayen"<<high;
   // ui->plot->graph(0)->addData(timestamp,high);
    ui->plot->replot();
}
//customPlot->xAxis->setTicks(false);
  //customPlot->yAxis->setTicks(false);
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearData()
{   timestamp.clear();
    high.clear();

}
void MainWindow::plot()
{   ui->plot->graph(0)->setData(timestamp,high);
    //ui->plot->xAxis->setRangeUpper(*std::max_element(timestamp.begin(),timestamp.end())*1.25);
    //ui->plot->xAxis->setRange(timestamp[0], timestamp[timestamp.length()-1]);
    //ui->plot->yAxis->setRangeUpper(*std::max_element(high.begin(),high.end())*1.25);
    //ui->plot->yAxis->setRange(*std::min_element(high.begin(), high.end()),*std::max_element(high.begin(),high.end()));
    ui->plot->graph(0)->rescaleAxes();
    ui->plot->replot();
    ui->plot->update(); //updates data
    ui->plot->yAxis->setTickLabels(true);

}
void MainWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
   //calculate two new data points:
 double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
 if (key-lastPointKey > 2) // at most add point every 6 s
  {     stock.updateDataByDay();
        QJsonObject dataByDay=stock.getDataByDay();
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
