#include "homepage.h"
#include "ui_homepage.h"
#include "companynewscard.h"
#include "watchlistcard.h"
#include "helper/helper.h"
#include "QString"

HomePage::HomePage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HomePage) {
  ui->setupUi(this);

  newsId = 0;
  currentUpdateStockId = 0;
  currentStockId = 0;
  loadedStocks = false;

  // setup a timer that repeatedly calls HomePage::realtimeUpdateStocks:
  connect(&timer, SIGNAL(timeout()), this, SLOT(realtimeUpdateStocks()));
  timer.start(0); // Interval 0 means to refresh as fast as possible
}

HomePage::~HomePage() {
  delete ui;
}

void HomePage::updateWatchlistStocks(QVector<Stock *> other_watchlistStocks) {
  watchlistStocks = other_watchlistStocks;

  if (watchlistStocks.isEmpty()) {
    return;
  }

  watchlistCards.clear();

  int stockId = 0;

  for (auto stock : watchlistStocks) {
    WatchlistCard *watchlistCard = new WatchlistCard(stock);
    ui->watchlist->layout()->addWidget(watchlistCard);
    watchlistCard->hide();
    connect(watchlistCard, &WatchlistCard::clicked, [this, stockId]() {
      this->changeCurrentStock(stockId);
    });
    stockId++;
    watchlistCards.append(watchlistCard);
  }

  ui->watchlist->layout()->addItem(new QSpacerItem(40, 20, QSizePolicy::Preferred,
                                   QSizePolicy::Expanding));

  stockGraphOneDay = new StockGraphOneDay(this);
  stockGraphThreeDays = new StockGraphThreeDays(this);
  stockGraphSixMonths = new StockGraphSixMonths(this);
  stockGraphOneMonth = new StockGraphOneMonth(this);

  for (int i = 0; i < watchlistStocks.size(); ++i) {
//    graphsOneDay.append(new StockGraphOneDay(watchlistStocks[i], this));
//    graphsThreeDays.append(new StockGraphThreeDays(watchlistStocks[i], this));
//    graphsSixMonths.append(new StockGraphSixMonths(watchlistStocks[i], this));
//    graphsOneMonth.append(new StockGraphOneMonth(watchlistStocks[i], this));

//    if (i > 0) {
//      graphsOneDay[i]->hide();
//      graphsThreeDays[i]->hide();
//      graphsSixMonths[i]->hide();
//      graphsOneMonth[i]->hide();
//    }
  }

  ui->oneDay->layout()->addWidget(stockGraphOneDay);
  ui->threeDays->layout()->addWidget(stockGraphThreeDays);
  ui->oneMonth->layout()->addWidget(stockGraphOneMonth);
  ui->sixMonths->layout()->addWidget(stockGraphSixMonths);

  newsId = 0;
  currentUpdateStockId = 0;
  currentStockId = 0;
  loadedStocks = false;
  watchlistCards[0]->setChecked(true);
  stockGraphOneDay->setStock(watchlistStocks[0]);
  stockGraphThreeDays->setStock(watchlistStocks[0]);
  stockGraphSixMonths->setStock(watchlistStocks[0]);
  stockGraphOneMonth->setStock(watchlistStocks[0]);
  realtimeUpdateStocks();
}

void HomePage::displayNews() {
  qDeleteAll(ui->stackedWidget->findChildren<CompanyNewsCard *>());
  QJsonArray companyNews = watchlistStocks[currentStockId]->getNews();

  int count = 0;

  for (auto v : companyNews) {
    QJsonObject json = v.toObject();
    long unixTimestamp = json["datetime"].toVariant().toInt();
    std::string readableTime = helper::convertToFullTimeReadable(unixTimestamp);

    CompanyNewsCard *companyNewsCard = new CompanyNewsCard(
      QString::number(++count),
      json["headline"].toString(),
      json["url"].toString(),
      QString(readableTime.c_str()),
      ui->stackedWidget);
    ui->stackedWidget->addWidget(companyNewsCard);
  }
}

void HomePage::displaySentimentAnalysis() {
  QJsonObject fullSentimentData =
    watchlistStocks[currentStockId]->getSentimentData();
  QJsonObject sentiment = fullSentimentData["sentiment"].toObject();
  qDebug() << sentiment << endl;
  ui->bearish->setText("Bearish Percentage:   " + QString::number(
                         sentiment["bearishPercent"].toDouble()));
  ui->bullish->setText("Bullish Percentage:   " + QString::number(
                         sentiment["bullishPercent"].toDouble()));
}

void HomePage::changeCurrentStock(int stockId) {
  if (currentStockId != stockId) {
    watchlistCards[currentStockId]->setChecked(false);
    watchlistCards[stockId]->setChecked(true);
    currentStockId = stockId;
    displayNews();
    displaySentimentAnalysis();
    stockGraphOneDay->setStock(watchlistStocks[currentStockId]);
    stockGraphThreeDays->setStock(watchlistStocks[currentStockId]);
    stockGraphSixMonths->setStock(watchlistStocks[currentStockId]);
    stockGraphOneMonth->setStock(watchlistStocks[currentStockId]);
  } else {
    watchlistCards[currentStockId]->setChecked(true);
  }
}

void HomePage::realtimeUpdateStocks() {
  if (watchlistStocks.isEmpty()) {
    return;
  }

  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key = time.elapsed() /
               1000.0; // time elapsed since start of demo, in seconds
  static double lastBatchKey = -1e9;
  static double lastKey = -1e9;

  if (currentUpdateStockId == 0) {
    if (key - lastBatchKey < 60) { // 1 minute
      return;
    } else {
      lastBatchKey = key;
    }
  }

  if (loadedStocks) {
    if (key - lastKey < 1) { // 1 second
      return;
    } else {
      lastKey = key;
    }
  }

  watchlistStocks[currentUpdateStockId]->updateNews();
  watchlistStocks[currentUpdateStockId]->updateSentimentData();
  watchlistStocks[currentUpdateStockId]->updateDataByDay();
  watchlistStocks[currentUpdateStockId]->updateDataByMinute();
  ui->watchlist->layout()->itemAt(currentUpdateStockId)->widget()->show();
  currentUpdateStockId = (currentUpdateStockId + 1) % watchlistStocks.size();

  if (currentUpdateStockId == 0 && !loadedStocks) {
    loadedStocks = true;
    displayNews();
    displaySentimentAnalysis();
  }
}

void HomePage::on_leftButton_clicked() {
  if (ui->stackedWidget->count() == 0 || newsId == 0) {
    return;
  }

  newsId = (newsId + ui->stackedWidget->count() - 1) % ui->stackedWidget->count();
  ui->stackedWidget->setCurrentIndex(newsId);
}

void HomePage::on_rightButton_clicked() {
  if (ui->stackedWidget->count() == 0 ||
      newsId == ui->stackedWidget->count() - 1) {
    return;
  }

  newsId = (newsId + 1) % ui->stackedWidget->count();
  ui->stackedWidget->setCurrentIndex(newsId);
}
