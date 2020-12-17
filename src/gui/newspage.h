#ifndef NEWSPAGE_H
#define NEWSPAGE_H

#include <QWidget>
#include "components/news.h"

namespace Ui {
class NewsPage;
}

class NewsPage : public QWidget {
  Q_OBJECT

 public:
  explicit NewsPage(QWidget *parent = nullptr);
  ~NewsPage();

 private:
  Ui::NewsPage *ui;
  News *news;
};

#endif // NEWSPAGE_H
