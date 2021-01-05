#ifndef STRATEGYDASHBOARD_H
#define STRATEGYDASHBOARD_H

#include <QWidget>
#include <QVector>
#include "strategygraph.h"
#include "../recommendation/Strategy/strategy.h"
#include "../components/stock.h"


namespace Ui {
class StrategyDashBoard;
}

class StrategyDashBoard : public QWidget
{
    Q_OBJECT

public:
    StrategyDashBoard(QWidget *parent);
    ~StrategyDashBoard();

private:

    Ui::StrategyDashBoard *ui;
    Stock *stock;
    Strategy *strategy;
    StrategyGraph *graph;
};

#endif // STRATEGYDASHBOARD_H
