#include "stockperformancerow.h"
#include "ui_stockperformancerow.h"

StockPerformanceRow::StockPerformanceRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockPerformanceRow)
{
    ui->setupUi(this);
}

StockPerformanceRow::~StockPerformanceRow()
{
    delete ui;
}
