#include "newspage.h"
#include "ui_newspage.h"

#include <string>

NewsPage::NewsPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::NewsPage) {
  ui->setupUi(this);

  news = new News();
  news->updateMarketNews();
}

NewsPage::~NewsPage() {
  delete ui;
  delete news;
}
