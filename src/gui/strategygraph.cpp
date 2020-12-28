#include "strategygraph.h"
#include "ui_strategygraph.h"
#include "../../../src/helper/helper.h"
#include <stdlib.h>
#include <math.h>
#include <QString>
#include "../../../src/components/stock.h"
#include "../../../src/recommendation/Strategy/ema_strategy.h"

StrategyGraph::StrategyGraph(QWidget *parent, QList<EMAStrategy*>& strategies, long& timePeriod) :
    QWidget(parent),
    ui(new Ui::StrategyGraph),
    strategies(strategies),
    timePeriod(timePeriod)
{
  ui->setupUi(this);
  ui->plot->setInteractions(QCP::iSelectLegend);
  ui->plot->legend->setVisible(true);
  ui->plot->legend->setSelectableParts(QCPLegend::spItems);
  ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->plot->yAxis2->setUpperEnding(QCPLineEnding::esSpikeArrow);
  ui->plot->yAxis2->setVisible(true);

  initLineCharts();
  initTimeRange();
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
  ui->plot->replot();


}

StrategyGraph::~StrategyGraph() {
  delete ui;
  strategies.clear();
}

void StrategyGraph::initLineCharts(){
    QList<Stock*> stockBlackList;
    QList<double> referenceBlackList;
    for (auto& it: this->strategies){
        if (not stockBlackList.contains(it->get_stock())){
            QColor stockChartColor(rand()% 256,rand()% 256,rand()% 256);
            QCPGraph* stockChart = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis);
            stockChart->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
                                       QPen(stockChartColor, 1.5), QBrush(Qt::white), 3));
            stockChart->setLineStyle(QCPGraph::lsLine);
            stockChart->setPen(QPen(stockChartColor, 2));
            QBrush shadowBrush(stockChartColor, Qt::Dense7Pattern);
            stockChart->setBrush(shadowBrush);
            std::string* temp = new std::string(it->get_stock()->getSymbol()+" : "+it->priceType);
            QString stockChartName(temp->c_str());
            stockChart->setName(stockChartName);
            stockChart->setVisible(true);
            this->stockCharts[it->get_stock()] = stockChart;
            stockBlackList.push_back(it->get_stock());
        }

        QColor strategyChartColor(rand()% 256,rand()% 256,rand()% 256);
        QCPGraph* strategyChart = new QCPGraph(ui->plot->xAxis, ui->plot->yAxis2);
        strategyChart->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
                                   QPen(strategyChartColor, 1.5), QBrush(Qt::white), 3));
        strategyChart->setLineStyle(QCPGraph::lsLine);
        strategyChart->setPen(QPen(strategyChartColor, 2));

        std::string* temp = new std::string(it->strategyName + " : " + it->get_stock()->getSymbol()+" ; "+it->priceType);
        QString strategyChartName(temp->c_str());
        strategyChart->setName(strategyChartName);
        strategyChart->setVisible(true);
        this->strategyCharts[it] = strategyChart;
        for(auto& reference: it->signalReferences){
            if(not referenceBlackList.contains(reference)){
            QCPItemLine* referenceLine = new QCPItemLine(ui->plot);
            referenceLine->setVisible(true);
            referenceLine->setPen(QPen(strategyChartColor, 2));
            referenceLine->setHead(QCPLineEnding::esSpikeArrow);
            referenceLine->setObjectName(it->strategyName.c_str());
            referenceLine->setVisible(true);
            referenceLine->start->setAxes(ui->plot->xAxis,ui->plot->yAxis2);
            referenceLine->end->setAxes(ui->plot->xAxis,ui->plot->yAxis2);
            this->referenceLines[reference] = referenceLine;
            referenceBlackList.push_back(reference);
            }
        }
    }
}

void StrategyGraph::initTimeRange(){
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd/MM hh:mm");
    double now = QDateTime::currentDateTime().toTime_t();
    // 86400 is the number of seconds per day: Here we show a 1-day interval
    ui->plot->xAxis->setRange(now - this->timePeriod, now+round(this->timePeriod/1000));
    ui->plot->yAxis->setTickLabels(false);
    ui->plot->xAxis->ticker()->setTickCount(10);
    ui->plot->xAxis->setTicker(dateTimeTicker);
    ui->plot->xAxis->setTickLabelRotation(15);
    ui->plot->rescaleAxes();
    ui->plot->xAxis->scaleRange(1.025, ui->plot->xAxis->range().center());
    ui->plot->yAxis->scaleRange(1.1, ui->plot->yAxis->range().center());
    ui->plot->yAxis2->scaleRange(1.1,ui->plot->yAxis2->range().center());
}

void StrategyGraph::realtimeDataSlot(){
    static QTime time(QTime::currentTime());
    double key = time.elapsed() /1000.0;
    static double lastPointKey = -1e9;
    if (key - lastPointKey >= 60){

       for(auto& it:this->stockCharts.keys()){
           it->updateDataByMinute();
       }
       this->timestamp = convert_to_vector(stockCharts.keys()[0]->getDataByMinute(),"t");
       long s = this->timestamp.size();
       for (auto& it:this->strategyCharts.keys()){
           it->update_numericSignals(s);

       }

       plot();
       lastPointKey = key;
    }

}

void StrategyGraph::plot(){
    for (auto& it: this->stockCharts.keys()){
    QJsonObject dummyData =  it->getDataByMinute();
    stockCharts[it]->setData(this->timestamp,convert_to_vector(dummyData,"c"));
    }

    for(auto& it: this->strategyCharts.keys()){
    strategyCharts[it]->setData(this->timestamp,it->numericSignals);
    }
    ui->plot->xAxis->setVisible(true);
    ui->plot->yAxis->setVisible(true);
    ui->plot->yAxis2->setVisible(true);
    ui->plot->replot();
    ui->plot->update();
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
