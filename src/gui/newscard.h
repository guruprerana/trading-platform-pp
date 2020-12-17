#ifndef NEWSCARD_H
#define NEWSCARD_H

#include <QWidget>

namespace Ui {
class NewsCard;
}

class NewsCard : public QWidget {
  Q_OBJECT

 public:
  explicit NewsCard(QString id, QString headline, QString category,
                    QString timestamp, QWidget *parent = nullptr);
  ~NewsCard();

  void debug();

 private:
  Ui::NewsCard *ui;
};

#endif // NEWSCARD_H
