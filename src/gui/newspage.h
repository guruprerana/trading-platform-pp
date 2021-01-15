#ifndef NEWSPAGE_H
#define NEWSPAGE_H

#include <QWidget>
#include "components/news.h"
#include <QVBoxLayout>

namespace Ui {
class NewsPage;
}

class NewsPage : public QWidget {
  Q_OBJECT

 public:
  explicit NewsPage(QWidget *parent = nullptr);
  ~NewsPage();
  void update();

 private:
  long latestTimestamp;
  Ui::NewsPage *ui;
  News *news;
  QVBoxLayout *layout;
};

#endif // NEWSPAGE_H
