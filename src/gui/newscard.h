#ifndef NEWSCARD_H
#define NEWSCARD_H

#include <QWidget>

namespace Ui {
class NewsCard;
}

class NewsCard : public QWidget
{
  Q_OBJECT

  public:
  explicit NewsCard(QWidget *parent = nullptr);
  ~NewsCard();

  private:
  Ui::NewsCard *ui;
};

#endif // NEWSCARD_H
