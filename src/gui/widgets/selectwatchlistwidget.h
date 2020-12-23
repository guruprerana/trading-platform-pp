#ifndef SELECTWATCHLISTWIDGET_H
#define SELECTWATCHLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QStringList>

const int LIST_ITEM_WIDGET_DATA_ROLE = 300;

namespace Ui {
class SelectWatchlistWidget;
}

class SelectWatchlistWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SelectWatchlistWidget(QWidget *parent = nullptr);
  ~SelectWatchlistWidget();

  QStringList getSelectedWatchList() const;

 private:
  Ui::SelectWatchlistWidget *ui;
};

#endif // SELECTWATCHLISTWIDGET_H
