#include "strategypage.h"
#include "ui_strategypage.h"

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

  drawStrategyGraph();
}

void StrategyPage::drawStrategyGraph() {
  auto stratSignals = strategy->simulate();

  if (strategy->get_name() == "SMA") {
    strategyGraph->drawSMA(
      strategy->timestamp_sma20,
      strategy->price_sma20,
      strategy->timestamp_sma50,
      strategy->price_sma50
    );
  }
}

void StrategyPage::changeCurrentStock(int stockId) {
  if (currentStockId != stockId) {
    watchlistCards[currentStockId]->setChecked(false);
    watchlistCards[stockId]->setChecked(true);
    strategyGraph->setStock(watchlistStocks[stockId]);
    strategy->set_stock(watchlistStocks[stockId]);
    drawStrategyGraph();
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
