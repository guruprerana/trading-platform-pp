#ifndef STRATEGYGRAPH_H
#define STRATEGYGRAPH_H

#include <QWidget>
#include <QTimer>
#include <QSet>
#include "../components/stock.h"
#include <QVariant>
#include "../library/qcustomplot.h"
#include "../recommendation/Strategy/ema_strategy.h"


namespace Ui {
class StrategyGraph;
}


class StrategyGraph : public QWidget
{
    Q_OBJECT
public:
    StrategyGraph();
    StrategyGraph(QWidget *parent, QList<EMAStrategy*>& strategies, long& timePeriod);
    ~StrategyGraph();
    void plot();
    void initLineCharts();
    void initTimeRange();

private slots:
    void realtimeDataSlot();

public:
 Ui::StrategyGraph *ui;
 QList<EMAStrategy*> strategies;
 QMap<Stock*, QCPGraph*> stockCharts;
 QMap<EMAStrategy*, QCPGraph*> strategyCharts;
 QMap<double, QCPItemLine*> referenceLines;
 QVector<double> timestamp;
 QTimer dataTimer;
 long timePeriod;
};

QVector<double> convert_to_vector(QJsonObject, std::string);
#endif // STRATEGYGRAPH_H
