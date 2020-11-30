#ifndef LEFTNAVIGATIONBAR_H
#define LEFTNAVIGATIONBAR_H

#include <QWidget>

namespace Ui {
class LeftNavigationBar;
}

class LeftNavigationBar : public QWidget {
  Q_OBJECT

 public:
  explicit LeftNavigationBar(QWidget *parent = nullptr);
  ~LeftNavigationBar();

 private slots:
  void on_homeButton_released();

  void on_tradeButton_released();

  void on_performanceButton_released();

  void on_newsButton_released();

  void on_marketsButton_released();

 private:
  Ui::LeftNavigationBar *ui;

 signals:
  void switchTab(QString tabName);
};

#endif // LEFTNAVIGATIONBAR_H
