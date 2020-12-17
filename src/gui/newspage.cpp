#include "newspage.h"
#include "ui_newspage.h"

#include <QDebug>
#include <QJsonObject>
#include "newscard.h"
#include "helper/helper.h"

#include <string>
#include <iostream>

NewsPage::NewsPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::NewsPage) {
  ui->setupUi(this);

  news = new News();
  layout = new QVBoxLayout(ui->scrollArea);

  QWidget *widget = new QWidget();
  widget->setLayout(layout);
  ui->scrollArea->setWidget(widget);

  news->updateMarketNews();

  auto newsArray = news->getMarketNews();

  int count = 0;

  for (auto v : newsArray) {
    QJsonObject json = v.toObject();
    long unixTimestamp = json["datetime"].toVariant().toInt();
    std::string readableTime = helper::convertToReadable(unixTimestamp);

    NewsCard *newsCard = new NewsCard(
      QString::number(++count),
      json["headline"].toString(),
      json["category"].toString(),
      QString(readableTime.c_str()),
      this);
    layout->addWidget(newsCard);
    newsCard->debug();
  }
}

NewsPage::~NewsPage() {
  delete ui;
  delete news;
}
