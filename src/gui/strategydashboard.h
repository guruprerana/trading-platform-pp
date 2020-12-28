#ifndef STRATEGYDASHBOARD_H
#define STRATEGYDASHBOARD_H

#include <QWidget>
#include <QVector>
#include "strategygraph.h"

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
    QList<Stock*> stocks;
    QList<EMAStrategy*> strategies;
    QList<StrategyGraph*> graphs;
};

#endif // STRATEGYDASHBOARD_H
