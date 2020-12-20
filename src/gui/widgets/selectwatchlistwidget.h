#ifndef SELECTWATCHLISTWIDGET_H
#define SELECTWATCHLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class SelectWatchlistWidget;
}

class SelectWatchlistWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SelectWatchlistWidget(QWidget *parent = nullptr);
  ~SelectWatchlistWidget();

 private:
  Ui::SelectWatchlistWidget *ui;
};

#endif // SELECTWATCHLISTWIDGET_H
