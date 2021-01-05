#ifndef STRATEGYGRAPH_H
#define STRATEGYGRAPH_H

#include <QWidget>
#include <QTimer>
#include <QSet>
#include "../components/stock.h"
#include <QVariant>
#include "../library/qcustomplot.h"
#include "../recommendation/Strategy/strategy.h"


namespace Ui {
class StrategyGraph;
}


class StrategyGraph : public QWidget
{
    Q_OBJECT
public:
    StrategyGraph();
    StrategyGraph(QWidget *parent, Strategy *strat, long& timePeriod);
    ~StrategyGraph();
    void plot();
    void initLineCharts();
    void initTimeRange();

private slots:
    void realtimeDataSlot();

public:
 Ui::StrategyGraph *ui;
 Strategy* strategy;
 QMap<Stock*, QCPGraph*> stockCharts;
 QMap<Strategy*, QCPGraph*> strategyCharts;
 QMap<double, QCPItemLine*> referenceLines; //for the moment don't try to plot the reference lines this will come after
 QVector<double> timestamp;
 QTimer dataTimer;
 long timePeriod; //to be deleted?
};

QVector<double> convert_to_vector(QJsonObject, std::string);
#endif // STRATEGYGRAPH_H
