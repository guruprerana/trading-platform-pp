#include "strategypage.h"
#include "ui_strategypage.h"
#include "signalcard.h"

StrategyPage::StrategyPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::StrategyPage) {
  ui->setupUi(this);
}

void StrategyPage::updateWatchlistStocks(QVector<Stock *>
    other_watchlistStocks) {
  watchlistStocks = other_watchlistStocks;

  if (watchlistStocks.isEmpty()) {
    return;
  }

  watchlistCards.clear();

  int stockId = 0;

  for (auto stock : watchlistStocks) {
    WatchlistCard *watchlistCard = new WatchlistCard(stock);
    ui->watchlist->layout()->addWidget(watchlistCard);
    connect(watchlistCard, &WatchlistCard::clicked, [this, stockId]() {
      this->changeCurrentStock(stockId);
    });
    stockId++;
    watchlistCards.append(watchlistCard);
  }

  ui->watchlist->layout()->addItem(new QSpacerItem(40, 20, QSizePolicy::Preferred,
                                   QSizePolicy::Expanding));

  strategyGraph = new StrategyGraph(this);
  ui->strategyWidget->layout()->addWidget(strategyGraph);

  currentStockId = 0;
  watchlistCards[0]->setChecked(true);
  strategyGraph->setStock(watchlistStocks[0]);
  strategy = new Strategy("SMA", watchlistStocks[0], false, "c");

  simulateStrategy();
}

void StrategyPage::simulateStrategy() {
  qDeleteAll(ui->scrollAreaWidgetContents->findChildren<SignalCard *>());

  while (ui->scrollAreaWidgetContents->layout()->count()) {
    QLayoutItem *layoutItem = ui->scrollAreaWidgetContents->layout()->itemAt(0);

    if (layoutItem->spacerItem()) {
      ui->scrollAreaWidgetContents->layout()->removeItem(layoutItem);
      // You could also use: layout->takeAt(i);
      delete layoutItem;
    }
  }

  strategy->simulate();

  if (strategy->get_name() == "SMA") {
    strategyGraph->drawSMA(
      strategy->timestamp_sma20,
      strategy->price_sma20,
      strategy->timestamp_sma50,
      strategy->price_sma50
    );

    for (auto &p : strategy->signals_sma) {
      ui->scrollAreaWidgetContents->layout()->addWidget(
        new SignalCard(p.first, p.second));
    }
  }

  else if (strategy->get_name() == "EMA") {
    strategyGraph->drawEMA(
      strategy->timestamp_ema6,
      strategy->price_ema6,
      strategy->timestamp_ema11,
      strategy->price_ema11
    );

    for (auto &p : strategy->signals_ema) {
      ui->scrollAreaWidgetContents->layout()->addWidget(
        new SignalCard(p.first, p.second));
    }
  }

  else if (strategy->get_name() == "MOM") {
    strategyGraph->drawMomentum(
      strategy->timestamp_mom,
      strategy->price_mom
    );

    if (!strategy->signals_mom.isEmpty()) {
      ui->scrollAreaWidgetContents->layout()->addWidget(
        new SignalCard(strategy->signals_mom.back().first,
                       strategy->signals_mom.back().second.second));
    }
  }

  else if (strategy->get_name() == "LR") {
    if (strategy->signals_lr.isEmpty()) {
      strategyGraph->drawLR(0, 0, strategy->timestamp_lr);
    } else {
      strategyGraph->drawLR(
        strategy->slope.back(),
        strategy->intercept.back(),
        strategy->timestamp_lr
      );
      ui->scrollAreaWidgetContents->layout()->addWidget(
        new SignalCard(strategy->signals_lr.back().first,
                       strategy->signals_lr.back().second));
    }
  }

  ui->scrollAreaWidgetContents->layout()->addItem(
    new QSpacerItem(40, 20,
                    QSizePolicy::Preferred,
                    QSizePolicy::Expanding));
}

void StrategyPage::changeCurrentStock(int stockId) {
  if (currentStockId != stockId) {
    watchlistCards[currentStockId]->setChecked(false);
    watchlistCards[stockId]->setChecked(true);
    strategyGraph->setStock(watchlistStocks[stockId]);
    strategy->set_stock(watchlistStocks[stockId]);
    simulateStrategy();
    currentStockId = stockId;
  } else {
    watchlistCards[currentStockId]->setChecked(true);
  }
}

StrategyPage::~StrategyPage() {
  delete ui;
  delete strategyGraph;
  delete strategy;
}

void StrategyPage::on_comboBox_currentIndexChanged(int index) {
  if (index == 0) {
    strategy->set_name("SMA");
  } else if (index == 1) {
    strategy->set_name("EMA");
  } else if (index == 2) {
    strategy->set_name("MOM");
  } else {
    strategy->set_name("LR");
  }

  simulateStrategy();
}
