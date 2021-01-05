#include "strategydashboard.h"
#include "ui_strategydashboard.h"


StrategyDashBoard::StrategyDashBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StrategyDashBoard) {
    ui->setupUi(this);
    ui->symbol->setText(QString("STRATEGY DASHBOARD"));

    long timePeriod = 86400; //no need because we always look at 6 months;


    //Setting attributes of the Dashboard Class
    Stock *var_stock = new Stock("AMZN");
    this->stock = var_stock;
    bool byMinute = false;
    std::string name = "EMA";
    std::string priceType = "c";
    Strategy *strat = new Strategy(name, var_stock,byMinute, priceType);
    this->strategy =  strat;//setting strategy attribute
    this->graph = new StrategyGraph(this, strat, timePeriod);//setting graph attribute


    ui->oneDay->layout()->addWidget(this->graph);
}

StrategyDashBoard::~StrategyDashBoard(){
    delete ui;
};
