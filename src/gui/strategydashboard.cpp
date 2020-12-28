#include "strategydashboard.h"
#include "ui_strategydashboard.h"


StrategyDashBoard::StrategyDashBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StrategyDashBoard) {
    ui->setupUi(this);
    ui->symbol->setText(QString("STRATEGY DASHBOARD"));

    // stocks.append(new Stock("AAPL")); // Apple
    // stocks.append(new Stock("MSFT")); // Microsoft
    stocks.append(new Stock("AMZN")); // Amazon
    // stocks.append(new Stock("FB")); // Facebook

    for(auto& it:stocks){

        // add strategies!
        bool byMinute = true;
        long timePeriod = 86400;
        std::string priceType01 = "c";
        std::string priceType02 = "o";
        std::string priceType03 = "h";
        std::string priceType04 = "l";
        strategies.append(new EMAStrategy(it,byMinute,priceType01));
        strategies.append(new EMAStrategy(it,byMinute,priceType02));
        strategies.append(new EMAStrategy(it,byMinute,priceType03));
        strategies.append(new EMAStrategy(it,byMinute,priceType04));
        graphs.append(new StrategyGraph(this,strategies,timePeriod));

    }
    ui->oneDay->layout()->addWidget(graphs[0]);
}

StrategyDashBoard::~StrategyDashBoard(){
    delete ui;
};
