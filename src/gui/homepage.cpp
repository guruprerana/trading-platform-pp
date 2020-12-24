#include "homepage.h"
#include "ui_homepage.h"
#include "companynewscard.h"
#include "watchlistcard.h"
#include "helper/helper.h"

HomePage::HomePage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HomePage) {
  ui->setupUi(this);
}

HomePage::~HomePage() {
  delete ui;
  delete stockGraphOneDay;
  delete stockGraphThreeDays;
  delete stockGraphOneMonth;
  delete stockGraphSixMonths;
}

void HomePage::updateWatchlistStocks(QVector<Stock *> other_watchlistStocks) {
  watchlistStocks = other_watchlistStocks;

  if (watchlistStocks.isEmpty()) {
    return;
  }

  newsId = 0;

  for (auto stock : watchlistStocks) {
    ui->watchlist->layout()->addWidget(new WatchlistCard(stock));
  }

  ui->watchlist->layout()->addItem(new QSpacerItem(40, 20, QSizePolicy::Preferred,
                                   QSizePolicy::Expanding));

  stockGraphOneDay = new StockGraphOneDay(watchlistStocks[0], this);
  stockGraphThreeDays = new StockGraphThreeDays(watchlistStocks[0], this);
  stockGraphSixMonths = new StockGraphSixMonths(watchlistStocks[0], this);
  stockGraphOneMonth = new StockGraphOneMonth(watchlistStocks[0], this);

  watchlistStocks[0]->updateNews();
  QJsonArray companyNews = watchlistStocks[0]->getNews();

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

  ui->oneDay->layout()->addWidget(stockGraphOneDay);
  ui->threeDays->layout()->addWidget(stockGraphThreeDays);
  ui->oneMonth->layout()->addWidget(stockGraphOneMonth);
  ui->sixMonths->layout()->addWidget(stockGraphSixMonths);
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
