#ifndef STOCKPERFORMANCEROW_H
#define STOCKPERFORMANCEROW_H

#include <QWidget>

namespace Ui {
class StockPerformanceRow;
}

class StockPerformanceRow : public QWidget
{
    Q_OBJECT

public:
    explicit StockPerformanceRow(QWidget *parent = nullptr);
    ~StockPerformanceRow();

private:
    Ui::StockPerformanceRow *ui;
};

#endif // STOCKPERFORMANCEROW_H
