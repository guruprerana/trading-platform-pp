#ifndef SELECTWATCHLISTWIDGET_H
#define SELECTWATCHLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QStringList>

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
  const int LIST_ITEM_WIDGET_DATA_ROLE = 300;

  Ui::SelectWatchlistWidget *ui;
};

#endif // SELECTWATCHLISTWIDGET_H
